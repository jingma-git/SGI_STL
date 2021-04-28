#pragma once
#include "m_iterator_base_types.h"

namespace mj
{
    template <class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T &value)
    {
        for (; first != last; ++first)
            *first = value;
    }

    template <class OutputIterator, class Size, class T>
    OutputIterator fill_n(OutputIterator first, Size n, const T &value)
    {
        for (; n > 0; --n, ++first)
            *first = value;
        return first;
    }

    //--------------------------------------------------
    // copy

    // All of these auxiliary functions serve two purposes.  (1) Replace
    // calls to copy with memmove whenever possible.  (Memmove, not memcpy,
    // because the input and output ranges are permitted to overlap.)
    // (2) If we're using random access iterators, then write the loop as
    // a for loop with an explicit count.
    // copy 函数-效率 memmove
    // copy 版本
    template <class _InputIter, class _OutputIter, class _Distance>
    inline _OutputIter __copy(_InputIter __first, _InputIter __last,
                              _OutputIter __result,
                              input_iterator_tag, _Distance *)
    {
        for (; __first != __last; ++__result, ++__first)
            *__result = *__first;
        return __result;
    }

    template <class _RandomAccessIter, class _OutputIter, class _Distance>
    inline _OutputIter
    __copy(_RandomAccessIter __first, _RandomAccessIter __last,
           _OutputIter __result, random_access_iterator_tag, _Distance *)
    {
        for (_Distance __n = __last - __first; __n > 0; --__n)
        {
            *__result = *__first;
            ++__first;
            ++__result;
        }
        return __result;
    }

    // 使用 memmove
    template <class _Tp>
    inline _Tp *
    __copy_trivial(const _Tp *__first, const _Tp *__last, _Tp *__result)
    {
        memmove(__result, __first, sizeof(_Tp) * (__last - __first));
        return __result + (__last - __first);
    }

} // namespace mj