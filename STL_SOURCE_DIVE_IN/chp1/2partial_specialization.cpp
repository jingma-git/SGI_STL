#include <iostream>
using namespace std;

template <typename I, typename O>
class TestClass
{
public:
    TestClass() { cout << "I, O" << endl; }
};

template <typename T>
class TestClass<T *, T *>
{
public:
    TestClass() { cout << "T*, T*" << endl; }
};

template <typename T>
class TestClass<const T *, T *>
{
public:
    TestClass() { cout << "const T*, T*" << endl; }
};

int main()
{
    TestClass<int, char> obj1;
    TestClass<int *, int *> obj2;
    TestClass<const int *, int *> obj3;
    TestClass<int *, char> obj4;
    return 0;
}