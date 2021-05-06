
// https://zhuanlan.zhihu.com/p/151777797
#include <stdio.h>
#include <string>
#include <iostream>
#include <complex>
using namespace std;
class Father
{
public:
    Father();
    ~Father();
    // f(int) and f(double) are overload
    virtual void f(int);
    virtual void f(double);

    virtual void g(int i = 10);

private:
};
void Father::f(int i)
{
    cout << "Father:f(int)" << endl;
}
void Father::f(double i)
{
    cout << "Father:f(double)" << endl;
}
void Father::g(int i)
{
    cout << "Father:g(int):i = " << i << endl;
}
Father::Father()
{
    cout << "new father" << endl;
}
Father::~Father()
{
    cout << "delete father" << endl;
}
class Child : public Father
{
public:
    Child();
    ~Child();
    // using Father::f; // ucomment this to see the 'hide' effect
    void f(complex<double> i);  // this->f() hides function Father::f(int), Father::f(double)
    virtual void g(int i = 20); // void g(int i = 20) override;

private:
};
void Child::f(complex<double> i)
{
    cout << "Child:f(complex<double>)" << endl;
}
void Child::g(int i)
{
    cout << "Child:g(int):i = " << i << endl;
}
Child::Child()
{
    cout << "new Child" << endl;
}
Child::~Child()
{
    cout << "delete Child" << endl;
}
int main()
{
    Father father;
    Child child;
    Father *fc = new Child;
    child.f(1); // hide father.f(int)
    father.f(1);
    child.f(0.1); // hide father.f(double)
    father.f(0.1);
    child.Father::f(1);
    child.Father::f(0.1);
    child.g();         // Child:g(int):i = 20, override father.g(int i=10)
    child.Father::g(); // Father:g(int):i = 10
    fc->g();           // Child:g(int):i = 10, why?

    // this is not saft, some resources in child will not be released
    // should declare virtual ~Father()
    delete fc;
    return 0;
}