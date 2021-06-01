#include <iostream>
#include <memory>

using namespace std;

class Base
{
};

class Derived : public Base
{
};

class MoreDerived : public Derived
{
};

int main()
{
    shared_ptr<Base> bPtr(new Base);
    shared_ptr<Base> bPtr1(bPtr);
    shared_ptr<Base> bPtr2 = bPtr1;
    cout << "base: " << bPtr.use_count() << ", " << bPtr1.use_count() << ", " << bPtr2.use_count() << endl;

    shared_ptr<Derived> dPtr(new Derived);
    shared_ptr<Base> dPtr1(dPtr);
    cout << "dervied: " << dPtr.use_count() << ", " << dPtr1.use_count() << endl;

    shared_ptr<MoreDerived> mPtr(new MoreDerived);
    dPtr1 = mPtr;
    shared_ptr<Derived> mPtr1(mPtr);
    cout << "morederived: " << mPtr.use_count() << ", " << dPtr1.use_count() << ", " << mPtr1.use_count() << endl;
    return 0;
}