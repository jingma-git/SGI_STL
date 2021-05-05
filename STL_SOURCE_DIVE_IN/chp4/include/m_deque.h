#pragma once
#include "m_alloc.h"
#include "m_iterator_base_types.h"
#include "m_uninitialized.h"
#include "m_algo.h"

namespace mj
{

    inline size_t _deque_buf_size(size_t sz)
    {
        return sz < 512 ? size_t(512 / sz) : size_t(1);
    }

    template <class T, class Ref, class Ptr>
    struct _deque_iterator
    {
        typedef _deque_iterator<T, T &, T *> iterator;
        typedef _deque_iterator<T, const T &, const T *> const_iterator;
        typedef _deque_iterator self;

        // five traits for iterator
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ptrdiff_t difference_type;

        typedef size_t size_type;

        typedef T **map_pointer;

        static size_t buffer_size()
        {
            return _deque_buf_size(sizeof(T));
        }

        void set_node(map_pointer new_node) // jump to next buffer
        {
            node = new_node;
            first = *new_node;
            last = first + difference_type(buffer_size());
        }

        reference operator*() const { return *cur; }
        pointer operator->() const { return &(operator*()); };

        // size from this iterator to x
        difference_type operator-(const self &x) const
        {
            return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
        }

        self &operator++()
        {
            ++cur;
            if (cur == last)
            {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        self operator++(int)
        {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self &operator--()
        {
            if (cur == first)
            {
                set_node(node - 1); // go to previous buffer
                cur = last;         // go to the last element of previous buffer
            }
            --cur;
            return *this;
        }

        // random access
        self &operator+=(difference_type n)
        {
            difference_type offset = n + (cur - first);
            if (offset >= 0 && offset < difference_type(buffer_size()))
                cur += n;
            else
            {
                difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size())
                                                         : -difference_type((-offset - 1) / buffer_size()) - 1;
                set_node(node + node_offset);
                cur = first + (offset - node_offset * difference_type(buffer_size()));
            }
            return *this;
        }

        self operator+(difference_type n) const
        {
            self tmp = *this;
            return tmp += n;
        }

        self &operator-=(difference_type n) { return *this += -n; }

        self operator-(difference_type n) const
        {
            self tmp = *this;
            return tmp -= n;
        }

        reference operator[](difference_type n) const { return *(*this + n); }
        bool operator==(const self &x) const { return cur == x.cur; }
        bool operator!=(const self &x) const { return !(*this == x); }
        bool operator<(const self &x) const
        {
            return (node == x.node) ? (cur < x.cur) : (node < x.node);
        }

        T *cur;           // current iter in buffer
        T *first;         // start of buffer
        T *last;          // end of buffer
        map_pointer node; // point to current buffer
    };

    template <class T, class Alloc = mj::allocator<T>, size_t BufSiz = 0>
    class deque
    {
    public:
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef size_t size_type;
        typedef _deque_iterator<T, T &, T *> iterator;
        typedef ptrdiff_t difference_type;

    protected:
        typedef pointer *map_pointer; // pointer to memory blocks (buffers)
        typedef mj::allocator<value_type> data_allocator;
        typedef mj::allocator<pointer> map_allocator;

    protected:
        // actual elements:
        // buf_first[start.cur--start.last]--buf*--buf_last[start.first--finish.cur]
        iterator start;
        iterator finish;

        map_pointer map;
        size_type map_size; // how may pointers map can store
        size_type initial_map_size;

        void create_map_and_nodes(size_type num_elements)
        {
            size_type num_nodes = num_elements / buffer_size() + 1;
            printf("num_nodes=%ld\n", num_nodes);
            map_size = mj::max(initial_map_size, num_nodes + 2);
            printf("map_size=%ld\n", map_size);
            map = map_allocator::allocate(map_size);
            // starting from middle and expand to two sides
            map_pointer nstart = map + (map_size - num_nodes) / 2;
            map_pointer nfinish = nstart + num_nodes - 1;
            map_pointer cur;
            for (cur = nstart; cur <= nfinish; ++cur)
            {
                *cur = allocate_node();
            }
            start.set_node(nstart);
            finish.set_node(nfinish);
            start.cur = start.first;
            finish.cur = finish.first + num_elements % buffer_size();
        }

        pointer allocate_node()
        {
            return data_allocator::allocate(buffer_size());
        }

        void deallocate_node(pointer p)
        {
            data_allocator::deallocate(p, buffer_size());
        }

        void destroy_nodes(map_pointer nstart, map_pointer nfinish)
        {
            for (map_pointer n = nstart; n < nfinish; ++n)
                deallocate_node(*n);
        }

        void push_back_aux(const value_type &value)
        {
            value_type v_copy = value;
            reserve_map_at_back();
            *(finish.node + 1) = allocate_node();
            try
            {
                construct(finish.cur, v_copy);
                finish.set_node(finish.node + 1);
                finish.cur = finish.first;
            }
            catch (...)
            {
                deallocate_node(*(finish.node + 1));
            }
        }

        void reserve_map_at_back(size_type nodes_to_add = 1)
        {
            if (nodes_to_add + 1 > map_size - (finish.node - map))
            {
                reallocate_map(nodes_to_add, false);
            }
        }

        void push_front_aux(const value_type &value)
        {
            value_type v_copy = value;
            reserve_map_at_front();
            *(start.node - 1) = allocate_node();
            try
            {
                start.set_node(start.node - 1);
                start.cur = start.last - 1;
                construct(start.cur, v_copy);
            }
            catch (...)
            {
                start.set_node(start.node + 1);
                start.cur = start.first;
                deallocate_node(*(start.node - 1));
                throw;
            }
        }

        void reserve_map_at_front(size_type nodes_to_add = 1)
        {
            if (nodes_to_add > start.node - map)
            {
                reallocate_map(nodes_to_add, true);
            }
        }

        void reallocate_map(size_type nodes_to_add, bool add_at_front)
        {
            size_type old_num_nodes = finish.node - start.node + 1;
            size_type new_num_nodes = old_num_nodes + nodes_to_add;

            map_pointer new_nstart;
            if (map_size > 2 * new_num_nodes)
            {
                new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
                if (new_nstart < start.node)
                {
                    copy(start.node, finish.node + 1, new_nstart);
                }
                else
                {
                    copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
                }
            }
            else
            {
                size_type new_map_size = map_size + mj::max(map_size, nodes_to_add) + 2;
                map_pointer new_map = map_allocator::allocate(new_map_size);
                new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
                copy(start.node, finish.node + 1, new_nstart);
                map_allocator::deallocate(map, map_size);
                map = new_map;
                map_size = new_map_size;
            }
            start.set_node(new_nstart);
            finish.set_node(new_nstart + old_num_nodes - 1);
        }

        void pop_back_aux()
        {
            deallocate_node(finish.first);
            finish.set_node(finish.node - 1);
            finish.cur = finish.last - 1;
            destroy(finish.cur);
        }

        void pop_front_aux()
        {
            destroy(start.cur);
            deallocate_node(start.first);
            start.set_node(start.node + 1);
            start.cur = start.first;
        }

    public:
        deque() : start(), finish(), map(0), map_size(0), initial_map_size(8)
        {
            create_map_and_nodes(0);
        }
        deque(int n, const value_type &value) : start(), finish(), map(0), map_size(0), initial_map_size(8)
        {
            fill_initialize(n, value);
        }

        ~deque()
        {
            if (map)
            {
                destroy_nodes(start.node, finish.node + 1);
                map_allocator::deallocate(map);
            }
        }

        static size_t buffer_size()
        {
            return _deque_buf_size(sizeof(T));
        }

        void fill_initialize(size_type n, const value_type &value)
        {
            create_map_and_nodes(n);
            map_pointer cur;

            for (cur = start.node; cur < finish.node; ++cur)
            {
                uninitialized_fill(*cur, *cur + buffer_size(), value);
            }
            uninitialized_fill(finish.first, finish.cur, value);
        }

        iterator begin() { return start; }
        iterator end() { return finish; }

        reference operator[](size_type n)
        {
            return start[difference_type(n)];
        }

        reference front() { return *start; }
        reference back()
        {
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }

        size_type size() const { return finish - start; }
        size_type max_size() const { return size_type(-1); }
        bool empty() const { return finish == start; }

        void push_back(const value_type &value)
        {
            if (finish.cur != finish.last - 1)
            {
                construct(finish.cur, value);
                ++finish.cur;
            }
            else
            {
                push_back_aux(value); // no space left in last buf
            }
        }

        void push_front(const value_type &value)
        {
            if (start.cur != start.first)
            {
                construct(start.cur - 1, value);
                --start.cur;
            }
            else
            {
                push_front_aux(value); // no space left in last buf
            }
        }

        void pop_back()
        {
            if (finish.cur != finish.first)
            {
                --finish.cur;
                destroy(finish.cur);
            }
            else
            {
                // no element in last buffer, so release space for last buffer
                pop_back_aux();
            }
        }

        void pop_front()
        {
            if (start.cur != start.last - 1)
            {
                destroy(start.cur);
                ++start.cur;
            }
            else
            {
                pop_front_aux();
            }
        }

        void clear()
        {
            for (map_pointer node = start.node + 1; node < finish.node; ++node)
            {
                destroy(*node, *node + buffer_size());
                deallocate_node(*node);
            }

            if (start.node != finish.node)
            {
                // there at least two buf left to destroy
                destroy(start.cur, start.last);
                destroy(finish.first, finish.cur);
                deallocate_node(finish.first);
            }
            else
            {
                // only one buf
                destroy(start.cur, finish.cur);
            }
            finish = start;
        }

        iterator erase(iterator pos)
        {
            iterator next = pos;
            ++next;
            difference_type index = pos - start;
            if (index < (size() >> 1)) // elements before pos is less than elements after pos
            {
                copy_backward(start, pos, next);
                pop_front();
            }
            else
            {
                copy(next, finish, pos);
                pop_back();
            }
            return start + index;
        }
    };
}; // namespace mj