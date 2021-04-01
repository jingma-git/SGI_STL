// set default template argument according to previous template
#include <iostream>
#include <cstddef>
using namespace std;

class alloc
{
};

template <typename T, typename Alloc = alloc, size_t BufSize = 0>
class deque
{
public:
    deque() { cout << "deque" << endl; }
};

// this is an adapter for real-container deque
template <typename T, typename Sequence = deque<T>>
class stack
{
public:
    stack() { cout << "stack" << endl; }

private:
    Sequence c;
};

int main()
{
    stack<int> s;
    return 0;
}