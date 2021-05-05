#pragma once
#include "m_vector.h"
#include "m_heap.h"
#include "m_function.h"

namespace mj
{
    template <class T, class Sequence = vector<T>,
              class Compare = less<typename Sequence::value_type>>
    class priority_queue
    {
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;
        typedef typename Sequence::size_type size_type;

    protected:
        Sequence c;
        Compare comp;

    public:
        priority_queue() : c() {}
        explicit priority_queue(const Compare &x) : c(), comp(x) {}

        template <class InputIter>
        priority_queue(InputIter first, InputIter last)
            : c(first, last)
        {
            make_heap(c.begin(), c.end(), comp);
        }

        template <class InputIter>
        priority_queue(InputIter first, InputIter last, const Compare &x)
            : c(first, last), comp(x)
        {
            make_heap(c.begin(), c.end(), comp);
        }

        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        reference top() { return c.front(); }
        const_reference top() const { return c.front(); }
        void push(const value_type &x)
        {
            c.push_back(x);
            push_heap(c.begin(), c.end(), comp);
        }

        void pop()
        {
            pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        }
    };

}