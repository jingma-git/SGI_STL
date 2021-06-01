#include <iostream>
using namespace std;

// notice: my implementation only ensures resource is not leaked, but cannot ensure correct reference count

class Base
{
};

class Derived : public Base
{
};

class MoreDerived : public Derived
{
};

template <class T>
class SmartPtr
{
public:
    SmartPtr() : ptr_(0) {}
    SmartPtr(T *ptr) : ptr_(ptr), ref_count_(1)
    {
    }

    ~SmartPtr()
    {
        --ref_count_;
        if (!ref_count_)
            delete ptr_;
    }

    // normal copy constructor
    SmartPtr(SmartPtr const &other)
        : ptr_(other.get())
    {
        ref_count_ = other.use_count() + 1;
        cout << "normal copy constructor" << endl;
    }

    // generalized copy constructor
    template <class U>
    SmartPtr(SmartPtr<U> const &other)
        : ptr_(other.get()) // restricts invalid conversion, eg. int*-->Base*
    {
        ref_count_ = other.use_count() + 1;
        cout << "generalized copy constructor" << endl;
    }

    // normal assignment operator
    SmartPtr &operator=(SmartPtr const &other)
    {
        ptr_ = other.get();
        ref_count_ = other.use_count() + 1;
        cout << "normal assignment constructor" << endl;
    }

    // generalized copy constructor
    template <class U>
    SmartPtr &operator=(SmartPtr<U> const &other)
    {
        ptr_ = other.get(); // restricts invalid conversion, eg. int*-->Base*
        ref_count_ = other.use_count() + 1;
        cout << "generalized assignment constructor" << endl;
    }

    T *get() const { return ptr_; }

    int use_count() const { return ref_count_; }

private:
    T *ptr_;
    mutable int ref_count_;
};

int main()
{
    // normal copy constructor
    SmartPtr<Base> bPtr(new Base);
    SmartPtr<Base> bPtr1(bPtr);
    cout << "bPtr.use_count=" << bPtr.use_count() << " bPtr1.use_count=" << bPtr1.use_count() << endl
         << endl;

    // generalized copy constructor works for inheritance
    SmartPtr<Derived> dPtr(new Derived);
    SmartPtr<Base> dPtr1(dPtr);
    cout << "dPtr.use_count=" << dPtr.use_count() << " dPtr1.use_count=" << dPtr1.use_count() << endl
         << endl;

    SmartPtr<MoreDerived> mPtr(new MoreDerived);
    SmartPtr<MoreDerived> mPtr1 = mPtr;
    SmartPtr<Derived> mPtr2 = mPtr;
    SmartPtr<Base> mPtr3 = mPtr;
    cout << "mPtr.use_count=" << mPtr.use_count() << endl;
    cout << "mPtr1.use_count=" << mPtr1.use_count() << endl;
    cout << "mPtr2.use_count=" << mPtr2.use_count() << endl;
    cout << "mPtr3.use_count=" << mPtr3.use_count() << endl;

    // SmartPtr<int> iPtr(new int);
    // SmartPtr<Base> bPtr2(iPtr); // error: cannot convert ‘int*’ to ‘Base*’ in initialization
    return 0;
}