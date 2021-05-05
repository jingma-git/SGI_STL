#pragma once
#include "m_iterator_base_types.h"
#include "m_ops.h"

namespace mj
{
    /// This is an overload used by find algos for the Input Iterator case.
    template <typename _InputIterator, typename _Predicate>
    inline _InputIterator
    __find_if(_InputIterator __first, _InputIterator __last,
              _Predicate __pred, input_iterator_tag)
    {
        while (__first != __last && !__pred(__first))
            ++__first;
        return __first;
    }

    /// This is an overload used by find algos for the RAI case.
    template <typename _RandomAccessIterator, typename _Predicate>
    _RandomAccessIterator
    __find_if(_RandomAccessIterator __first, _RandomAccessIterator __last,
              _Predicate __pred, random_access_iterator_tag)
    {
        typename iterator_traits<_RandomAccessIterator>::difference_type
            __trip_count = (__last - __first) >> 2;

        for (; __trip_count > 0; --__trip_count)
        {
            if (__pred(__first))
                return __first;
            ++__first;

            if (__pred(__first))
                return __first;
            ++__first;

            if (__pred(__first))
                return __first;
            ++__first;

            if (__pred(__first))
                return __first;
            ++__first;
        }

        switch (__last - __first)
        {
        case 3:
            if (__pred(__first))
                return __first;
            ++__first;
        case 2:
            if (__pred(__first))
                return __first;
            ++__first;
        case 1:
            if (__pred(__first))
                return __first;
            ++__first;
        case 0:
        default:
            return __last;
        }
    }

    template <typename _Iterator, typename _Predicate>
    inline _Iterator
    __find_if(_Iterator __first, _Iterator __last, _Predicate __pred)
    {
        typedef typename iterator_traits<_Iterator>::iterator_category category;
        return __find_if(__first, __last, __pred, category());
    }

    template <typename Iterator, typename T>
    Iterator find(Iterator first, Iterator last, const T &val)
    {
        return __find_if(first, last, mj::__iter_equals_val(val));
    }
} // namespace mj
