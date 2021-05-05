#include <iostream>
#include <memory>
using namespace std;

template <class T1, class T2>
inline void construct(T1 *pointer, const T2 &value)
{
    new (pointer) T1(value);
}
int main()
{
    int x = 10;
    construct(&x, 100);
    cout << x << endl;

#ifdef __USE_MALLOC
    cout << "use class __malloc_alloc_template" << endl;
#else
    cout << "use class __default_alloc_template" << endl;
#endif
    return 0;
}