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
            _Construct(&*__first, __x); // call constructor
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

    // uninitialized_copy 调用 copy constructor

    // Valid if copy construction is equivalent to assignment, and if the
    //  destructor is trivial.
    template <class _InputIter, class _ForwardIter>
    inline _ForwardIter
    __uninitialized_copy_aux(_InputIter __first, _InputIter __last,
                             _ForwardIter __result,
                             __true_type)
    {
        return mj::copy(__first, __last, __result);
    }

    template <class _InputIter, class _ForwardIter>
    inline _ForwardIter
    __uninitialized_copy_aux(_InputIter __first, _InputIter __last,
                             _ForwardIter __result,
                             __false_type)
    {
        _ForwardIter __cur = __result;
        try
        {
            for (; __first != __last; ++__first, ++__cur)
                _Construct(&*__cur, *__first);
            return __cur;
        }
        catch (...)
        {
            _Destroy(__result, __cur);
            throw;
        }
    }

    template <class _InputIter, class _ForwardIter, class _Tp>
    inline _ForwardIter
    __uninitialized_copy(_InputIter __first, _InputIter __last,
                         _ForwardIter __result, _Tp *)
    {
        typedef typename __type_traits<_Tp>::is_POD_type _Is_POD;
        return __uninitialized_copy_aux(__first, __last, __result, _Is_POD());
    }

    // 内存的配置与对象的构造行为分离开来。
    template <class _InputIter, class _ForwardIter>
    inline _ForwardIter
    uninitialized_copy(_InputIter __first, _InputIter __last,
                       _ForwardIter __result)
    {
        return __uninitialized_copy(__first, __last, __result,
                                    value_type(__result));
    }
};