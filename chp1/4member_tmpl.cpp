#include <iostream>

using namespace std;
class alloc
{
};

template <class T, class Alloc = alloc>
class vector
{
public:
    typedef T value_type;
    typedef value_type *iterator;

    template <typename I>
    void insert(iterator position, I first, I second) { cout << "insert" << endl; }
};

int main()
{
    int a[4] = {1, 2, 3, 4};
    vector<int> x;
    vector<int>::iterator it;
    x.insert(it, a, a + 4);
    return 0;
}