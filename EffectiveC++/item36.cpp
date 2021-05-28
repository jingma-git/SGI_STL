#include <iostream>
using namespace std;

class B
{
public:
    // virtual void mf()
    // {
    //     cout << "B::mf()" << endl;
    // }

    void mf()
    {
        cout << "B::mf()" << endl;
    }
};

class D : public B
{
public:
    // virtual void mf()
    // {
    //     cout << "D::mf()" << endl;
    // }

    void mf()
    {
        cout << "D::mf()" << endl;
    }
};

int main()
{
    D d;
    B *pd1 = &d;
    D *pd2 = &d;
    pd1->mf();
    pd2->mf();
    return 0;
}