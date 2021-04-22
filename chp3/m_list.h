#pragma once
#include "m_def.h"
#include "m_alloc.h"
#include "m_iterator_base_funcs.h"

namespace mj
{

    template <typename T>
    struct _list_node
    {
        _list_node<T> *prev;
        _list_node<T> *next;
        T value;
    };

    template <typename T>
    struct _list_iterator
    {
        typedef _list_iterator<T> iterator;
        typedef _list_iterator<T> _Self;
        typedef _list_node<T> _Node;

        typedef mj::bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;

        _list_iterator(_Node *_node) : node(_node) {}
        _list_iterator() {}
        _list_iterator(const iterator &i) : node(i.node) {}

        reference operator*() const
        {
            return node->value;
        }

        pointer operator->() const { return &(operator*()); }

        _Self &operator++()
        {
            node = node->next;
            return *this;
        }

        _Self operator++(int)
        {
            _Self tmp = *this;
            ++(*this);
            return tmp;
        }

        _Self &operator--()
        {
            node = node->prev;
            return *this;
        }

        _Self operator--(int)
        {
            _Self tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const _Self &i) const
        {
            return node == i.node;
        }

        bool operator!=(const _Self &i) const
        {
            return node != i.node;
        }

        _Node *node;
    };

    template <typename T, class Alloc = mj::allocator<T>>
    class list
    {
    public:
        typedef _list_iterator<T> iterator;
        typedef _list_node<T> _Node;
        typedef mj::allocator<_Node> _Node_alloc;

        typedef typename iterator::reference reference;
        typedef typename iterator::pointer pointer;
        typedef typename iterator::value_type value_type;

    public:
        list() { empty_initialize(); }
        ~list()
        {
            _Node *cur = node->next;
            while (cur != node)
            {
                _Node *next = cur->next;
                // _Node_alloc::destroy(cur);
                // _Node_alloc::deallocate(cur);
                delete cur;
                cur = next;
            }
        }

    protected:
        void empty_initialize()
        {
            node = get_node();
            node->prev = node;
            node->next = node;
        }

        _Node *get_node()
        {
            // _Node *newnode = new _Node;
            // return _Node_alloc::allocate(1);
            return (new _Node);
        }

        _Node *create_node(const T &value)
        {
            _Node *p = get_node();
            p->value = value;
        }

    public:
        //iterators
        iterator begin()
        {
            return node->next;
        }

        iterator end()
        {
            return node;
        }

        //capacity
        bool empty()
        {
            return node.next == node;
        }

        size_t size()
        {
            return mj::distance(begin(), end());
        }

        reference front() { return *begin(); }

        reference back() { return *(--end()); }

        //modifiers
        iterator insert(iterator pos, const T &value)
        {
            // insert before pos
            _Node *newnode = create_node(value);
            newnode->next = pos.node;
            newnode->prev = pos.node->prev->prev;
            pos.node->prev->next = newnode;
            pos.node->prev = newnode;
        }

        void push_front(const T &value)
        {
            insert(begin(), value);
        }

        void pop_front(const T &value)
        {
        }

        void push_back(const T &value)
        {
            insert(end(), value);
        }

        void pop_back(const T &value)
        {
        }

    private:
        _Node *node;
    };

};