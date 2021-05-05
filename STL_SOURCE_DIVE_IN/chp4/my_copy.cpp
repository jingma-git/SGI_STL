#include "m_algobase.h"
#include "m_algo.h"
#include <iostream>

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
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        cout << "output end overlap with input trivial" << endl;
        mj::copy(ia + 2, ia + 7, ia);
        mj::for_each(ia, ia + 9, display<int>());
        cout << endl;
    }

    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        cout << "output start overlap with input trivial" << endl;
        mj::copy(ia + 2, ia + 7, ia + 4);
        mj::for_each(ia, ia + 9, display<int>());
        cout << endl;
    }
}