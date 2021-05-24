#pragma once

template <typename T>
struct NumTraits;

template <>
struct NumTraits<int>
{
    typedef int Real;
    typedef double FloatingPoint;
    enum
    {
        IsComplex = 0,
        HasFloatingPoint = 0,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 1
    };
};

template <>
struct NumTraits<float>
{
    typedef float Real;
    typedef float FloatingPoint;
    enum
    {
        IsComplex = 0,
        HasFloatingPoint = 1,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 1
    };
};

template <>
struct NumTraits<double>
{
    typedef double Real;
    typedef double FloatingPoint;
    enum
    {
        IsComplex = 0,
        HasFloatingPoint = 1,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 1
    };
};

template <typename _Real>
struct NumTraits<std::complex<_Real>>
{
    typedef _Real Real;
    typedef std::complex<_Real> FloatingPoint;
    enum
    {
        IsComplex = 1,
        HasFloatingPoint = NumTraits<Real>::HasFloatingPoint,
        ReadCost = 2,
        AddCost = 2 * NumTraits<Real>::AddCost,
        MulCost = 4 * NumTraits<Real>::MulCost + 2 * NumTraits<Real>::AddCost
    };
};

template <>
struct NumTraits<long long int>
{
    typedef long long int Real;
    typedef long double FloatingPoint;
    enum
    {
        IsComplex = 0,
        HasFloatingPoint = 0,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 1
    };
};

template <>
struct NumTraits<long double>
{
    typedef long double Real;
    typedef long double FloatingPoint;
    enum
    {
        IsComplex = 0,
        HasFloatingPoint = 1,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 1
    };
};

template <>
struct NumTraits<bool>
{
    typedef bool Real;
    typedef float FloatingPoint;
    enum
    {
        IsComplex = 0,
        HasFloatingPoint = 0,
        ReadCost = 1,
        AddCost = 1,
        MulCost = 1
    };
};