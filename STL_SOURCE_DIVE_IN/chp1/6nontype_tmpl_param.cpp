// set default template argument according to previous template
#include <iostream>
#include <cstddef>
using namespace std;

class alloc
{
};

template <typename T, typename Ref, typename Ptr, size_t BufSize>
struct __deque_iterator
{
    static int buffer_size()
    {
        int n = BufSize;
        return n != 0 ? n : (n < 512 ? 512 / sizeof(T) : size_t(1));
    };
};

template <typename T, typename Alloc = alloc, size_t BufSize = 0>
class deque
{
public:
    typedef __deque_iterator<T, T &, T *, BufSize> iterator;
    typedef __deque_iterator<T, const T &, const T *, BufSize> const_iterator;
};

int main()
{
    cout << deque<float>::iterator::buffer_size() << endl;
    cout << deque<int, alloc, 64>::iterator::buffer_size() << endl;
    return 0;
}