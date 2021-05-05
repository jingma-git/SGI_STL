#include "m_list.h"
#include <iostream>

using namespace std;

struct A
{
    A() : x(-1) {}
    A(int x) : x(x) {}

    int x;
};

int main()
{
    using namespace mj;
    list<A *> aptrs, garbage;
    // aptrs.push_back(new A(0));
    // aptrs.push_back(new A(1));
    // aptrs.push_back(new A(1));
    // aptrs.push_back(new A(2));
    // list<A *>::iterator b = aptrs.begin();
    // aptrs.erase(++b);

    for (auto it = aptrs.begin(); it != aptrs.end(); ++it)
    {
        if (*it)
            delete (*it);
    }

    for (auto it = garbage.begin(); it != garbage.end(); ++it)
    {
        if (*it)
            delete (*it);
    }
    return 0;
}