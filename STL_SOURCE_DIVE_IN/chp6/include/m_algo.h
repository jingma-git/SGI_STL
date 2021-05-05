#pragma once
#include "m_ops.h"
#include "m_iterator_base_funcs.h"
#include "m_algobase.h"
namespace mj
{
    template <class InputIter, class Function>
    Function for_each(InputIter first, InputIter last, Function f)
    {
        for (; first != last; ++first)
            f(*first);
        return f;
    }

    template <class T>
    inline const T &max(const T &a, const T &b)
    {
        if (a < b)
            return b;
        else
            return a;
    }

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

    template <class _ForwardIter, class _Tp, class _Distance>
    _ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
                               const _Tp &__val, _Distance *)
    {
        _Distance __len = distance(__first, __last);
        _Distance __half;
        _ForwardIter __middle;

        while (__len > 0)
        {
            __half = __len >> 1;
            __middle = __first;
            advance(__middle, __half);
            if (*__middle < __val)
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
            else
                __len = __half;
        }
        return __first;
    }

    template <class _ForwardIter, class _Tp>
    inline _ForwardIter lower_bound(_ForwardIter __first, _ForwardIter __last,
                                    const _Tp &__val)
    {
        return __lower_bound(__first, __last, __val,
                             __DISTANCE_TYPE(__first));
    }

    template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
    _ForwardIter __lower_bound(_ForwardIter __first, _ForwardIter __last,
                               const _Tp &__val, _Compare __comp, _Distance *)
    {
        _Distance __len = distance(__first, __last);
        _Distance __half;
        _ForwardIter __middle;

        while (__len > 0)
        {
            __half = __len >> 1;
            __middle = __first;
            advance(__middle, __half);
            if (__comp(*__middle, __val))
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
            else
                __len = __half;
        }
        return __first;
    }

    template <class _ForwardIter, class _Tp, class _Compare>
    inline _ForwardIter lower_bound(_ForwardIter __first, _ForwardIter __last,
                                    const _Tp &__val, _Compare __comp)
    {
        return __lower_bound(__first, __last, __val, __comp,
                             __DISTANCE_TYPE(__first));
    }

    template <class _ForwardIter, class _Tp, class _Distance>
    _ForwardIter __upper_bound(_ForwardIter __first, _ForwardIter __last,
                               const _Tp &__val, _Distance *)
    {
        _Distance __len = 0;
        distance(__first, __last, __len);
        _Distance __half;
        _ForwardIter __middle;

        while (__len > 0)
        {
            __half = __len >> 1;
            __middle = __first;
            advance(__middle, __half);
            if (__val < *__middle)
                __len = __half;
            else
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
        }
        return __first;
    }

    template <class _ForwardIter, class _Tp>
    inline _ForwardIter upper_bound(_ForwardIter __first, _ForwardIter __last,
                                    const _Tp &__val)
    {
        return __upper_bound(__first, __last, __val,
                             __DISTANCE_TYPE(__first));
    }

    template <class _ForwardIter, class _Tp, class _Compare, class _Distance>
    _ForwardIter __upper_bound(_ForwardIter __first, _ForwardIter __last,
                               const _Tp &__val, _Compare __comp, _Distance *)
    {
        _Distance __len = 0;
        distance(__first, __last, __len);
        _Distance __half;
        _ForwardIter __middle;

        while (__len > 0)
        {
            __half = __len >> 1;
            __middle = __first;
            advance(__middle, __half);
            if (__comp(__val, *__middle))
                __len = __half;
            else
            {
                __first = __middle;
                ++__first;
                __len = __len - __half - 1;
            }
        }
        return __first;
    }

    template <class _ForwardIter, class _Tp, class _Compare>
    inline _ForwardIter upper_bound(_ForwardIter __first, _ForwardIter __last,
                                    const _Tp &__val, _Compare __comp)
    {
        return __upper_bound(__first, __last, __val, __comp,
                             __DISTANCE_TYPE(__first));
    }

    template <class _RandomAccessIter>
    inline void __insertion_sort(_RandomAccessIter first, _RandomAccessIter last)
    {
        if (first == last)
            return;

        _RandomAccessIter cur = first;
        for (_RandomAccessIter i = first + 1; i != last; ++i)
        {
            __linear_insert(first, i, value_type(first));
            // _RandomAccessIter inner = first;
            // for (; inner != cur; ++inner)
            // {
            //     if (*cur < *inner)
            //     {
            //         copy_backward(inner, cur, inner);
            //         *inner = *cur;
            //     }
            // }
        }
    }

    template <class _RandomAccessIter, class T>
    inline void __linear_insert(_RandomAccessIter first, _RandomAccessIter last, T *)
    {
        T value = *last;
        if (value < *first)
        {
            copy_backward(first, last, last + 1);
            *first = value;
        }
        else
        {
            __unguarded_linear_insert(last, value);
        }
    }

    template <class _RandomAccessIter, class T>
    inline void __unguarded_linear_insert(_RandomAccessIter last, T value)
    {
        _RandomAccessIter next = last;
        --next;
        while (value < *next)
        {
            *last = *next;
            last = next;
            --next;
        }
        *last = value;
    }
}