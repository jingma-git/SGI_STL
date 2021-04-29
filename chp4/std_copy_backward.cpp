#include <iostream>
#include <algorithm>
#include <deque>

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
    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        cout << "output end overlap with input, no problem!" << endl;
        copy_backward(ia + 2, ia + 7, ia + 9);
        for_each(ia, ia + 9, display<int>());
        cout << endl;
    }

    {
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        cout << "output start overlap with input trivial" << endl;
        copy_backward(ia + 2, ia + 7, ia + 4);
        for_each(ia, ia + 9, display<int>());
        cout << endl;
    }

    {
        cout << "output start overlap with input non-trivial" << endl;
        int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        deque<int> id(ia, ia + 9);
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        advance(first, 2);
        cout << *first << endl;
        advance(last, -2);
        cout << *last << endl;

        deque<int>::iterator result = id.begin();
        advance(result, 5);
        copy_backward(first, last, result);
        for_each(id.begin(), id.end(), display<int>());
        cout << endl;
    }
    return 0;
}