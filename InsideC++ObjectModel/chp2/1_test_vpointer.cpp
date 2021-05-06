#include <iostream>
using namespace std;
// https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/
class A
{
    void print() {}
    virtual void dance() {} // comment this, you will find sizeof(A)==1
};

int main()
{
    A a;
    cout << sizeof(A) << endl;
    return 0;
}