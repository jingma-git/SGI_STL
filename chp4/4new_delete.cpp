// new, void* operator new(size_t), placement new
// placement new syntax: new (pointer) T() // eg. new (void*) A()
#include <iostream>
#include "m_algobase.h"
#include <vector>
using namespace std;

struct A
{
    A()
    {
        x = 0;
        cout << "A is constructed" << endl;
    }

    A(int x_) : x(x_)
    {
        cout << "A is constructed x=" << x << endl;
    }

    int x;
};

int main()
{
    cout << "A:" << sizeof(A) << " int: " << sizeof(int) << endl;
    A *ptr = static_cast<A *>(::operator new(5 * sizeof(A)));
    A *ptr1 = (A *)malloc(5 * sizeof(A));

    new (ptr) A(); // placement new
    mj::fill_n(ptr, 3, A());

    A *iter = ptr;
    for (; iter < ptr + 5; ++iter)
    {
        cout << iter->x << endl;
    }

    ::operator delete(ptr);
    free(ptr1);
    return 0;
}