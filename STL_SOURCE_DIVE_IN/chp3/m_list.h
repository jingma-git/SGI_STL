#pragma once
#include "m_def.h"
#include "m_alloc.h"
#include "m_iterator_base_funcs.h"
#include <stdio.h>

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

        template <class InputIterator>
        list(InputIterator first, InputIterator last)
        {
            empty_initialize();
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }

        ~list()
        {
            clear();
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
            return _Node_alloc::allocate(1);
            // return (new _Node);
        }

        _Node *create_node(const T &value)
        {
            _Node *p = get_node();
            p->value = value;
            return p;
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
            return node->next == node;
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
            newnode->prev = pos.node->prev;
            pos.node->prev->next = newnode;
            pos.node->prev = newnode;
            return newnode;
        }

        iterator erase(iterator pos)
        {
            _Node *next = pos.node->next;
            _Node *prev = pos.node->prev;
            prev->next = next;
            next->prev = prev;
            _Node_alloc::destroy(pos.node);
            return iterator(next);
        }

        void push_front(const T &value)
        {
            insert(begin(), value);
        }

        void pop_front()
        {
            erase(begin());
        }

        void push_back(const T &value)
        {
            insert(end(), value);
        }

        void pop_back(const T &value)
        {
            erase(--end());
        }

        void clear()
        {
            _Node *cur = node->next;
            while (cur != node)
            {
                _Node *tmp = cur;
                cur = cur->next;
                _Node_alloc::destroy(tmp);
                _Node_alloc::deallocate(tmp);
            }
            node->next = node;
            node->prev = node;
        }

        void remove(const T &value)
        {
            iterator first = begin();
            iterator last = end();
            while (first != last)
            {
                iterator next = first;
                ++next;
                if (*first == value)
                {
                    erase(first);
                }
                first = next;
            }
        }

        void unique()
        {
            // remove continous same elements
            iterator first = begin();
            iterator last = end();
            if (first == last)
                return;

            iterator next = first;
            while (++next != last)
            {
                if (*first == *next)
                {
                    erase(next);
                }
                else
                {
                    first = next;
                }
                next = first;
            }
        }

        void transfer(iterator position, iterator first, iterator last)
        {
            if (position != last)
            {
                // from back to front, change next pointer
                (last.node->prev)->next = position.node;
                (first.node->prev)->next = last.node;
                (position.node->prev)->next = first.node;
                // from back to front, change prev pointer
                _Node *tmp = position.node->prev;
                (position.node)->prev = (last.node)->prev;
                (last.node)->prev = (first.node)->prev;
                (first.node)->prev = tmp;
            }
        }

    private:
        _Node *node;
    };

}; // namespace mj