#include <iostream>
using namespace std;

struct X
{
};

struct Y : virtual public X
{
};

struct Z : virtual public X
{
};

struct A : public Y, public Z
{
};

int main()
{
    cout << "sizeof(X)=" << sizeof(X) << endl; // one char to store X object's memory address
    cout << "sizeof(Y)=" << sizeof(Y) << endl; // __vbc (virtual base class) to X
    cout << "sizeof(Z)=" << sizeof(Z) << endl; // __vbc to Y
    cout << "sizeof(A)=" << sizeof(A) << endl; // sizeof(Y) + sizeof(Z)

    // sizeof(X)=1
    // sizeof(Y)=8
    // sizeof(Z)=8
    // sizeof(A)=16
    return 0;
}