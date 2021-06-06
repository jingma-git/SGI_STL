#include <iostream>
using namespace std;

template <int n>
struct Factorial
{
    enum
    {
        value = Factorial<n - 1>::value * n
    };
};

template <>
struct Factorial<0>
{
    enum
    {
        value = 1
    };
};

int main()
{

    cout << Factorial<4>::value << endl;
    return 0;
}