#pragma once
#include "m_algobase.h"
#include "m_type_traits.h"
#include "m_iterator_base_funcs.h"
#include "m_construct.h"

namespace mj
{

    template <class _ForwardIter, class _Size, class _Tp>
    inline _ForwardIter __uninitialized_fill_n_aux(_ForwardIter __first, _Size __n, const _Tp &__x, __true_type)
    {
        printf("trivial initalization!\n");
        return fill_n(__first, __n, __x);
    }

    template <class _ForwardIter, class _Size, class _Tp>
    inline _ForwardIter __uninitialized_fill_n_aux(_ForwardIter __first, _Size __n, const _Tp &__x, __false_type)
    {
        printf("non-trivial initalization!\n");
        for (; __n > 0; --__n, ++__first)
        {
            _Construct(&*__first, __x);
        }
        return __first;
    }

    template <class _ForwardIter, class _Size, class _Tp, class _Tp1>
    inline _ForwardIter
    __uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp &__x, _Tp1 *)
    {
        typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
        return __uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
    }

    template <class FowardIterator, class Size, class T>
    FowardIterator uninitialized_fill_n(FowardIterator first, Size n, const T &x)
    {
        typedef typename __type_traits<T>::is_POD_type _Is_POD;
        __uninitialized_fill_n(first, n, x, value_type(first));
    }
};