#pragma once
#include "m_iterator_base_types.h"
#include "m_iterator_base_funcs.h"
#include "m_type_traits.h"
#include "m_config.h"
#include <stdio.h>
#include <string.h>
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
        printf("copy input_iterator\n");
        for (; __first != __last; ++__result, ++__first)
            *__result = *__first;
        return __result;
    }

    template <class _RandomAccessIter, class _OutputIter, class _Distance>
    inline _OutputIter
    __copy(_RandomAccessIter __first, _RandomAccessIter __last,
           _OutputIter __result, random_access_iterator_tag, _Distance *)
    {
        printf("copy random access\n");
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
        printf("copy trivial\n");
        memmove(__result, __first, sizeof(_Tp) * (__last - __first));
        return __result + (__last - __first);
    }
#if defined(_MJ_CLASS_PARTIAL_SPECIALIZATION)
    // class partial specialzation
    template <class InputIter, class OutputIter, class BoolType>
    struct __copy_dispatch // primary template
    {
        OutputIter operator()(InputIter first, InputIter last, OutputIter result)
        {
            typedef typename iterator_traits<InputIter>::difference_type _Distance;
            return __copy(first, last, result, iterator_category(first), (_Distance *)(0));
        }
    };

    template <class T>
    struct __copy_dispatch<T *, T *, __true_type> //partial specialzation
    {
        T *operator()(T *first, T *last, T *result)
        {
            return __copy_trivial(first, last, result);
        }
    };

    template <class T>
    struct __copy_dispatch<const T *, T *, __true_type> //partial specialzation
    {
        T *operator()(const T *first, const T *last, T *result)
        {
            return __copy_trivial(first, last, result);
        }
    };

    // interface
    template <class InputIter, class OutputIter>
    inline OutputIter copy(InputIter first, InputIter last, OutputIter result)
    {
        typedef typename iterator_traits<InputIter>::value_type _Tp;
        typedef typename __type_traits<_Tp>::has_trivial_assignment_operator _Trivial;
        return __copy_dispatch<InputIter, OutputIter, _Trivial>()(first, last, result);
    }
#else
    template <class _InputIter, class _OutputIter>
    inline _OutputIter copy(_InputIter __first, _InputIter __last,
                            _OutputIter __result)
    {
        typedef typename iterator_traits<_InputIter>::difference_type _Distance;
        return __copy(__first, __last, __result,
                      iterator_category(__first),
                      (_Distance *)(0));
    }

#define __MJ_COPY_TRIVIAL(_Tp)                                       \
    inline _Tp *copy(const _Tp *first, const _Tp *last, _Tp *result) \
    {                                                                \
        memmove(result, first, sizeof(_Tp) * (last - first));        \
        return result + (last - first);                              \
    }

    __MJ_COPY_TRIVIAL(char)
    __MJ_COPY_TRIVIAL(signed char)
    __MJ_COPY_TRIVIAL(unsigned char)
    __MJ_COPY_TRIVIAL(short)
    __MJ_COPY_TRIVIAL(unsigned short)
    __MJ_COPY_TRIVIAL(int)
    __MJ_COPY_TRIVIAL(unsigned int)
    __MJ_COPY_TRIVIAL(long)
    __MJ_COPY_TRIVIAL(unsigned long)
    __MJ_COPY_TRIVIAL(long long)
    __MJ_COPY_TRIVIAL(unsigned long long)
    __MJ_COPY_TRIVIAL(float)
    __MJ_COPY_TRIVIAL(double)
    __MJ_COPY_TRIVIAL(long double)
#undef __MJ_COPY_TRIVIAL
#endif

    //--------------------------------------------------
    // copy_backward
    // 逆向复制
    template <class _BidirectionalIter1, class _BidirectionalIter2,
              class _Distance>
    inline _BidirectionalIter2 __copy_backward(_BidirectionalIter1 __first,
                                               _BidirectionalIter1 __last,
                                               _BidirectionalIter2 __result,
                                               bidirectional_iterator_tag,
                                               _Distance *)
    {
        while (__first != __last)
            *--__result = *--__last;
        return __result;
    }

    template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
    inline _BidirectionalIter __copy_backward(_RandomAccessIter __first,
                                              _RandomAccessIter __last,
                                              _BidirectionalIter __result,
                                              random_access_iterator_tag,
                                              _Distance *)
    {
        for (_Distance __n = __last - __first; __n > 0; --__n)
            *--__result = *--__last;
        return __result;
    }

    // This dispatch class is a workaround for compilers that do not
    // have partial ordering of function templates.  All we're doing is
    // creating a specialization so that we can turn a call to copy_backward
    // into a memmove whenever possible.

    template <class _BidirectionalIter1, class _BidirectionalIter2,
              class _BoolType>
    struct __copy_backward_dispatch
    {
        typedef typename iterator_traits<_BidirectionalIter1>::iterator_category
            _Cat;
        typedef typename iterator_traits<_BidirectionalIter1>::difference_type
            _Distance;

        static _BidirectionalIter2 copy(_BidirectionalIter1 __first,
                                        _BidirectionalIter1 __last,
                                        _BidirectionalIter2 __result)
        {
            return __copy_backward(__first, __last, __result, _Cat(), (_Distance *)0);
        }
    };

    template <class _Tp>
    struct __copy_backward_dispatch<_Tp *, _Tp *, __true_type>
    {
        static _Tp *copy(const _Tp *__first, const _Tp *__last, _Tp *__result)
        {
            printf("copy backward trivial!\n");
            const ptrdiff_t _Num = __last - __first;
            memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
            return __result - _Num;
        }
    };

    template <class _Tp>
    struct __copy_backward_dispatch<const _Tp *, _Tp *, __true_type>
    {
        static _Tp *copy(const _Tp *__first, const _Tp *__last, _Tp *__result)
        {
            return __copy_backward_dispatch<_Tp *, _Tp *, __true_type>::copy(__first, __last, __result);
        }
    };

    template <class _BI1, class _BI2>
    inline _BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {
        // __STL_REQUIRES(_BI1, _BidirectionalIterator);
        // __STL_REQUIRES(_BI2, _Mutable_BidirectionalIterator);
        // __STL_CONVERTIBLE(typename iterator_traits<_BI1>::value_type,
        //                   typename iterator_traits<_BI2>::value_type);
        typedef typename __type_traits<typename iterator_traits<_BI2>::value_type>::has_trivial_assignment_operator
            _Trivial;
        return __copy_backward_dispatch<_BI1, _BI2, _Trivial>::copy(__first, __last, __result);
    }

} // namespace mj