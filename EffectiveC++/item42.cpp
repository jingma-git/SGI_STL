#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Base
{
private:
    struct NestedClass
    {
    };

public:
    typedef NestedClass Nested;
};

template <typename T>
class Derived : public Base<T>::Nested // should not specify typename in Base class list
{
public:
    Derived() : Base<T>::Nested() // should not specify typename in member intialization list
    {
        typename Base<T>::Nested n; // must specify typename!!!
    }
};

template <typename ConstIter>
void print_val(ConstIter it)
{
    typedef typename std::iterator_traits<ConstIter>::value_type value_type;
    const value_type &val = *it;
    cout << val << endl;
}

int main()
{
    int a[3] = {0, 1, 2};
    std::vector<int> l(a, a + 3);
    print_val(a + 1);
    print_val(l.begin());
    return 0;
}