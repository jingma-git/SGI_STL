#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class print
{
public:
    void operator()(const T &ele)
    {
        cout << ele << " ";
    };
};

int main()
{
    int a[4] = {1, 2, 3, 4};
    for_each(a, a + 4, print<int>()); // print<int>() is a temporary object
    return 0;
}