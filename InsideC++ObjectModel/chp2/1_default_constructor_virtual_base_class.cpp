#include <iostream>
using namespace std;

struct B
{
    int n;
    B(int x) : n(x)
    {
        cout << "B: n=" << n << endl;
    }
};

struct X : virtual B
{
    X() : B(1)
    {
        cout << "X: n=" << n << endl;
    }
};

struct Y : virtual B
{
    Y() : B(2)
    {
        cout << "Y: n=" << n << endl;
    }
};

struct AA : X, Y
{
    AA() : B(3), X(), Y() {}
};

int main()
{
    AA aa;
    return 0;
}