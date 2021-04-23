#pragma once
#include "m_alloc.h"
#include "m_iterator_base_types.h"

namespace mj
{

    inline size_t _deque_buf_size(size_t sz)
    {
        return sz < 512 ? size_t(512 / sz) : size_t(1);
    }

    template <class T>
    struct _deque_iterator
    {
        typedef _deque_iterator<T> iterator;
        typedef _deque_iterator<T> self;

        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef random_access_iterator_tag iterator_category;
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

        difference_type operator-(const self &x) const
        {
            return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
        }

        T *cur;
        T *first; // buffer
        T *last;  // buffer
        map_pointer node;
    };

    template <class T, class Alloc = mj::allocator<T>, size_t BufSiz = 0>
    class deque
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef size_t size_type;

    protected:
        typedef pointer *map_pointer; // pointer to memory blocks (buffers)

    protected:
        map_pointer map;
        size_type map_size;
    };
}; // namespace mj