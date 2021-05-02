#pragma once
#include <new> // used for placement new
#include "m_type_traits.h"
namespace mj
{
    template <class T1, class T2>
    inline void _Construct(T1 *p, const T2 &value)
    {
        new (p) T1(value); // placement new
    }

    template <class T>
    inline void _Construct(T *p)
    {
        new (p) T();
    }

    // construct() 接受一个指针 __p 和 一个初值 __value。
    template <class _T1, class _T2>
    inline void construct(_T1 *__p, const _T2 &__value)
    {
        _Construct(__p, __value);
    }

    template <class _T1>
    inline void construct(_T1 *__p)
    {
        _Construct(__p);
    }

    // 第一个版本，接受一个指针，准备将该指针所指之物析构掉。
    template <class _Tp>
    inline void destroy(_Tp *__pointer)
    {
        __pointer->~_Tp();
    }

    // 若是 __false_type，这才以循环的方式遍历整个范围，并在循环中每经历一个对象就调用第一个版本的 destory()。
    // 这是 non-trivial destructor
    template <class _ForwardIterator>
    void
    __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
    {
        printf("destroy non-trivial\n");
        for (; __first != __last; ++__first)
            destroy(&*__first);
    }

    // 若是 __true_type，什么都不做；这是 trivial destructor。
    template <class _ForwardIterator>
    inline void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type)
    {
        printf("destroy trivial\n");
    }

    // 利用__type_traits<T>判断该类型的析构函数是否需要做什么。
    template <class _ForwardIterator, class _Tp>
    inline void
    __destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp *)
    {
        typedef typename __type_traits<_Tp>::has_trivial_destructor
            _Trivial_destructor;
        __destroy_aux(__first, __last, _Trivial_destructor());
    }

    // 调用 value_type(iterator) 获得迭代器所指对象的类别。
    template <class _ForwardIterator>
    inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
        __destroy(__first, __last, value_type(__first));
    }

    // 第二版本，destroy 泛型特化
    inline void _Destroy(char *, char *) {}
    inline void _Destroy(int *, int *) {}
    inline void _Destroy(long *, long *) {}
    inline void _Destroy(float *, float *) {}
    inline void _Destroy(double *, double *) {}

    // 第二个版本，接受 __first 和 __last 两个迭代器，将 [__first, __last)范围内的所有对象析构掉。
    template <class _ForwardIterator>
    inline void destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
        _Destroy(__first, __last);
    }
}; // namespace mj