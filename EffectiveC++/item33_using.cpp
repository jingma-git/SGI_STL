#include <iostream>
using namespace std;

class Base
{
public:
    virtual void mf1() = 0;
    virtual void mf1(int)
    {
        cout << "virtual Base::mf1(int)" << endl;
    }

    virtual void mf2()
    {
        cout << "virtual Base::mf2()" << endl;
    }

    void mf3()
    {
        cout << "Base::mf3()" << endl;
    }

    void mf3(double)
    {
        cout << "Base::mf3(double)" << endl;
    }
};

class Derived : public Base
{
public:
    using Base::mf1;
    using Base::mf3; // make all things in Base named mf1 and mf3 visible in Derived's scope

    virtual void mf1()
    {
        cout << "virtual Derived::mf1()" << endl;
    }

    void mf3()
    {
        cout << "Derived::mf3()" << endl;
    }

    void mf4()
    {
        cout << "Derived::mf4()" << endl;
    }
};

int main()
{
    Derived d;
    int x;
    d.mf1();
    d.mf1(x);
    d.mf3();
    d.mf3(x);
    return 0;
}