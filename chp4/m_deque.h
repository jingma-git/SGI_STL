#pragma once
#include "m_alloc.h"
#include "m_iterator_base_types.h"

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

        size_t buffer_size()
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
        typedef T *pointer;
        typedef size_t size_type;
        typedef _deque_iterator<T, T &, T *> iterator;
        typedef ptrdiff_t difference_type;

    protected:
        typedef pointer *map_pointer; // pointer to memory blocks (buffers)

    protected:
        iterator start;
        iterator finish;

        map_pointer map;
        size_type map_size; // how may pointers map can store
    public:
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
    };
}; // namespace mj