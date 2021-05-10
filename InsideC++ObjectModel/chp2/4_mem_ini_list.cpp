#include <iostream>
#include <string>
using namespace std;

// initialize reference member
class Ref
{
};

class TestRef
{
    TestRef(Ref &ref_) : ref(ref_) {}
    Ref &ref;
};

// initialize a const member
class TestConst
{
    TestConst() : x(0) {}
    const int x;
};

// intialize base_class/member with argments
class Base
{
public:
    Base(string name_) : name(name) {}
    string name;
};

class Compoent
{
public:
    Compoent(string name_) : name(name_) {}
    string name;
};

class Derived : public Base
{
    Derived() : Base(""), comp("") {}
    Derived(string name_, string comp_name_) : Base(name_), comp(comp_name_) {}
    Compoent comp;
};

int main()
{
    return 0;
}