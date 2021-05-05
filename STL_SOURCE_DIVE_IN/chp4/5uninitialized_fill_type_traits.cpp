#include <iostream>
#include "m_uninitialized.h"
using namespace std;
// uncomment printf in "m_uninitialized.h"
// decides whether to call constructor
struct A
{
};

int main()
{
    int ints[5];
    int *intptrs[5];
    A as[5];
    A *aptrs[5];
    mj::uninitialized_fill_n(ints, 3, 2);           // raw datatype has trivial constructor and deconstructor
    mj::uninitialized_fill_n(intptrs, 3, &ints[0]); // raw pointer has trivial constructor and deconstructor
    mj::uninitialized_fill_n(as, 2, A());
    mj::uninitialized_fill_n(aptrs, 2, &as[0]); // raw pointer has trivial constructor and deconstructor
    mj::destroy(aptrs, aptrs + 5);
    // A *aptr = static_cast<A *>(::operator new(5 * sizeof(A)));
    // mj::destroy(aptr, aptr + 5);
    // ::operator delete(aptr);
    return 0;
}