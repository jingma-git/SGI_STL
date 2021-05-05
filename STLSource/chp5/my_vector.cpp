#include "m_vector.h"
#include "m_algo.h"
#include <iostream>

using namespace std;

template <class T>
struct display
{
    void operator()(const T &val)
    {
        cout << val << " ";
    }
};
int main()
{
    mj::vector<int> v1(10, 1);
    mj::vector<int> v2(12, 2);
    v1.swap(v2);
    cout << "v1: " << v1.size() << endl;
    mj::for_each(v1.begin(), v1.end(), display<int>());
    cout << endl;
    cout << "v2: " << v2.size() << endl;
    mj::for_each(v2.begin(), v2.end(), display<int>());
    cout << endl;
    return 0;
}