#pragma once
#include <iostream>

namespace m_math
{
    class Rational
    {
    public:
        Rational(int numerator = 0, int denominator = 1) : m_numerator(numerator), m_denominator(denominator) {}

        int numerator() const { return m_numerator; }
        int denominator() const { return m_denominator; }

    private:
        int m_numerator;
        int m_denominator;
    };

    const Rational operator*(const Rational &a, const Rational &b);

    inline std::ostream &operator<<(std::ostream &out, const Rational &a)
    {
        out << a.numerator() << "/" << a.denominator();
        return out;
    }
}

// template <typename T>
// const T inverse(const T &x);