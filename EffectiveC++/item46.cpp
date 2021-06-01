#include <iostream>
using namespace std;

template <typename T>
class Rational;

template <typename T>
const Rational<T> doAdd(const Rational<T> &a, const Rational<T> &b);

template <typename T>
class Rational
{
public:
    Rational(T numerator = 0, T denominator = 1) : m_numerator(numerator), m_denominator(denominator) {}
    T numerator() const { return m_numerator; }
    T denominator() const { return m_denominator; }

    // implicit inline for short definition
    friend const Rational operator*(Rational const &lhs, Rational const &rhs)
    {
        return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
    }

    // avoid code bloat by letting the inline function call the complex function
    friend const Rational operator+(Rational const &lhs, Rational const &rhs)
    {
        return doAdd(lhs, rhs);
    }

private:
    T m_numerator;
    T m_denominator;
};

int main()
{
    Rational<int> oneFourth(1, 4);
    Rational<int> result;
    result = oneFourth * 2; // Implicit conversion Rational(2, 1)
    result = 2 * oneFourth; // Implicit conversion Rational(2, 1)
    result = oneFourth + 2; // Implicit conversion Rational(2, 1)
    result = 2 + oneFourth; // Implicit conversion Rational(2, 1)
    return 0;
}

template <typename T>
const Rational<T> doAdd(const Rational<T> &lhs, const Rational<T> &rhs)
{
    return Rational<T>(lhs.numerator() + rhs.numerator(), lhs.denominator() + rhs.denominator());
}