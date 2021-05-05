#include <list>
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
    A *arr[4] = {new A(0), new A(1), new A(2), new A(3)};
    list<A *> aptrs;
    list<A *> garbage;
    aptrs.push_back(arr[0]);
    aptrs.push_back(arr[1]);
    aptrs.push_back(arr[2]);
    aptrs.push_back(arr[3]);
    list<A *>::iterator b = aptrs.begin();
    garbage.push_back(*b); // comment this will lead to memory leak
    aptrs.erase(b);

    // for (auto it = aptrs.begin(); it != aptrs.end(); ++it)
    // {
    //     if (*it)
    //         delete (*it);
    // }

    // for (auto it = garbage.begin(); it != garbage.end(); ++it)
    // {
    //     if (*it)
    //         delete (*it);
    // }
    for (int i = 0; i < 4; ++i)
    {
        delete arr[i];
    }
    return 0;
}