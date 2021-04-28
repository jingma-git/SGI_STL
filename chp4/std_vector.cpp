#include <vector>
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
    vector<A *> aptrs;
    return 0;
}