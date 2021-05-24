#include <iostream>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

// Use template keyword when calling template_member_function inside template_func whose paramter depends on unknown_template_parameter
// otherwise you will get error "no match for operator <".

// At compile time, the compiler cannot know that dst.triangularView is a member template
// and that the following < symbol is part of the delimiter for the template parameter.
// Another possibility would be that dst.triangularView is
// a member variable with the < symbol refering to the operator<() function

template <typename T>
class Number
{
public:
    Number(const T &val) : m_val(val)
    {
        cout << "Number=" << m_val << " sizeof(T)=" << sizeof(T) << endl;
    }

    template <typename U>
    U as_type() const
    {
        return static_cast<U>(m_val);
    }

private:
    T m_val;
};

template <typename T>
int to_int(const Number<T> &num)
{
    // return num.as_type<int>();
    return num.template as_type<int>();
}

template <typename T>
int to_double(const Number<T> &num)
{
    // return num.as_type<int>();
    return num.template as_type<double>();
}

void testNumber()
{
    Number<short> a(10);
    int int_a = to_int(a);
    double double_a = to_double(a);
    cout << int_a << " sizeof(int_a)=" << sizeof(int_a) << endl;
    cout << double_a << " sizeof(double_a)=" << sizeof(double_a) << endl;
}

template <class Derived, class OtherDerived>
void copyUpper(MatrixBase<Derived> const &dst, const MatrixBase<OtherDerived> &src)
// void copyUpper(MatrixXf &dst, const MatrixXf &src)
{
    const_cast<MatrixBase<Derived> &>(dst).template triangularView<Upper>() = src.template triangularView<Upper>();
}

void testMatrixXf()
{
    MatrixXf dst = MatrixXf::Random(5, 5);
    MatrixXf src = MatrixXf::Ones(6, 6);
    copyUpper(dst.block(0, 0, 4, 4), src.block(0, 0, 4, 4));
    cout << "dst\n";
    cout << dst << endl;
}

int main()
{
    // testNumber();
    testMatrixXf();
    return 0;
}