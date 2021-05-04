#pragma once

namespace mj
{
    template <class _Arg, class _Result>
    struct unary_function
    {
        typedef _Arg argument_type;
        typedef _Result result_type;
    };

    template <class _Arg1, class _Arg2, class _Result>
    struct binary_function
    {
        typedef _Arg1 first_argument_type;
        typedef _Arg2 second_argument_type;
        typedef _Result result_type;
    };

    template <class _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x + __y; }
    };

    template <class _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x - __y; }
    };

    template <class _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x * __y; }
    };

    template <class _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x / __y; }
    };

    template <class _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x, const _Tp &__y) const { return __x % __y; }
    };

    template <class _Tp>
    struct negate : public unary_function<_Tp, _Tp>
    {
        _Tp operator()(const _Tp &__x) const { return -__x; }
    };

    template <class _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x == __y; }
    };

    template <class _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x != __y; }
    };

    template <class _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x > __y; }
    };

    template <class _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x < __y; }
    };

    template <class _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x >= __y; }
    };

    template <class _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x <= __y; }
    };

    template <class _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x && __y; }
    };

    template <class _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
        bool operator()(const _Tp &__x, const _Tp &__y) const { return __x || __y; }
    };

    template <class _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
        bool operator()(const _Tp &__x) const { return !__x; }
    };

    // identity is an extensions: it is not part of the standard.
    template <class _Tp>
    struct _Identity : public unary_function<_Tp, _Tp>
    {
        const _Tp &operator()(const _Tp &__x) const { return __x; }
    };

    template <class _Tp>
    struct identity : public _Identity<_Tp>
    {
    };
}