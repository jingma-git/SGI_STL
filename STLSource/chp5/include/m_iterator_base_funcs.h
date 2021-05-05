#pragma once
#include "m_iterator_base_types.h"

namespace mj
{
    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        // return input_iterator_tag() or output_iterator_tag() or forward_iterator_tag()
        // or bidirectional_iterator_tag() or random_access_iterator_tag()
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }

    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }

    template <class _Iter>
    inline typename iterator_traits<_Iter>::difference_type *
    distance_type(const _Iter &)
    {
        return static_cast<typename iterator_traits<_Iter>::difference_type *>(0);
    }

#define __ITERATOR_CATEGORY(__i) iterator_category(__i)
#define __DISTANCE_TYPE(__i) distance_type(__i)
#define __VALUE_TYPE(__i) value_type(__i)

    template <typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <typename RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    template <typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return _distance(first, last, category());
    }

    template <class _InputIter, class _Distance>
    inline void __advance(_InputIter &__i, _Distance __n, input_iterator_tag)
    {
        while (__n--)
            ++__i;
    }

    template <class _BidirectionalIterator, class _Distance>
    inline void __advance(_BidirectionalIterator &__i, _Distance __n,
                          bidirectional_iterator_tag)
    {
        if (__n >= 0)
            while (__n--)
                ++__i;
        else
            while (__n++)
                --__i;
    }

    template <class _RandomAccessIterator, class _Distance>
    inline void __advance(_RandomAccessIterator &__i, _Distance __n,
                          random_access_iterator_tag)
    {
        __i += __n;
    }

    template <class _InputIterator, class _Distance>
    inline void advance(_InputIterator &__i, _Distance __n)
    {
        __advance(__i, __n, iterator_category(__i));
    }
};