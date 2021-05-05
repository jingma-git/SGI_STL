#include <iostream>
#include "m_vector.h"
#include "m_heap.h"
#include "m_algo.h"

using namespace std;

template <class T>
struct display
{
    void operator()(const T &x)
    {
        cout << x << " ";
    }
};

int main()
{
    using namespace mj;
    // int ia[10] = {68, 31, 65, 21, 24, 32, 26, 19, 16, 13};
    int ia[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> ivec(ia, ia + 10);

    make_heap(ivec.begin(), ivec.end());
    for_each(ivec.begin(), ivec.end(), display<int>());
    cout << endl;

    // ivec.push_back(50);
    // push_heap(ivec.begin(), ivec.end());
    // for_each(ivec.begin(), ivec.end(), display<int>());
    // cout << endl;

    // pop_heap(ivec.begin(), ivec.end());
    // cout << ivec.back() << endl;
    // for_each(ivec.begin(), ivec.end(), display<int>());
    // cout << endl;

    // sort_heap(ivec.begin(), ivec.end());
    // for_each(ivec.begin(), ivec.end(), display<int>());
    // cout << endl;

    return 0;
}