
#include <iostream>
using namespace std;

struct V
{
    virtual void f()
    {
        cout << "V::f" << endl;
    }

    virtual void g()
    {
        cout << "V::g" << endl;
    }
};

struct A : virtual V
{
    virtual void f()
    {
        cout << "A::f" << endl;
    }
};

struct B : virtual V
{
    virtual void g()
    {
        cout << "B::g" << endl;
    }

    B(V *, A *);
};

struct D : A, B
{
    virtual void f()
    {
        cout << "D::f" << endl;
    }

    virtual void g()
    {
        cout << "D::g" << endl;
    }

    D() : B((A *)this, this)
    {
    }
};

B::B(V *v, A *a)
{
    f();
    g();

    v->g();
    a->f();
}

int main()
{
    D d;
    return 0;
}