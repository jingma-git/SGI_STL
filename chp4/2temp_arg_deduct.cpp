// function template argument deduction
#include <iostream>
using namespace std;

template <class T> // #1 primary temp
void f(T a)
{
    cout << "f(T a)" << endl;
}

template <class T> // #2 primary temp (overloaded)
void f(T *a)
{
    cout << "f(T* a)" << endl;
}

template <class T>
void f(const T *a)
{
    cout << "f(const T* a)" << endl;
}

template <> // specialization for #2 f<int>(int*)
void f<>(int *a)
{
    cout << "f<int>(int*)" << endl;
}

struct A
{
};

template <class T>
struct B
{
    template <class R> // #1
    int operator*(R &)
    {
        cout << "B<T> * R" << endl;
    }
};

template <class T, class R> // #2
int operator*(T &, R &)
{
    cout << "T * R" << endl;
}

int main()
{
    // f(1);
    // double a = 2;
    // f(&a);
    // int b = 3;
    // f(&b);
    const int *p;
    f(p);

    // A a;
    // B<int> b;
    // b *a; // #1: R=A, #2 T=B<A>, R=A
    return 0;
}