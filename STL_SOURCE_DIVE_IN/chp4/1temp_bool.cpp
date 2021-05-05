// https://stackoverflow.com/questions/23711389/template-with-bool-parameter
#include <iostream>
using namespace std;

template <bool islist>
struct A;

template <>
struct A<true>
{
    static const int val = 1;
};

template <>
struct A<false>
{
    static const int val = 0;
};

int main()
{
    cout << A<true>::val << endl;
    cout << A<false>::val << endl;
    return 0;
}