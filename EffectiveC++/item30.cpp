#include "item30.h"
// #include <iostream>
// using namespace std;
// https://stackoverflow.com/questions/24858014/checking-the-code-generated-implicitly-by-the-c-compiler
// https://stackoverflow.com/questions/1443982/when-do-compilers-inline-c-code
int main()
{
    // cout << 1 * 2 << endl;
    m_math::Rational one_half(1, 2), one_fourth(1, 4);
    m_math::Rational result = one_half * one_fourth;
    // cout << result << endl;
    // double x_inv = inverse(3.0);
    // cout << x_inv << endl;
    // int int_inv = inverse(3.0);
    // cout << int_inv << endl;
    return 0;
}

namespace m_math
{
    const Rational operator*(const Rational &a, const Rational &b)
    {
        return Rational(a.numerator() * b.numerator(), a.denominator() * b.denominator());
    }
}

// template <typename T>
// const T operator*(const T &a, const T &b)
// {
//     cout << "template is being called" << endl;
//     return a * b;
// }

// template <typename T>
// const T inverse(const T &x)
// {
//     T res = 1.0 / x;
//     cout << "template inverse is being called: " << res << endl;
//     return res;
// }