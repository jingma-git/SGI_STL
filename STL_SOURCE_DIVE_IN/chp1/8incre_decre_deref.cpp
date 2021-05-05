#include <iostream>
using namespace std;

class Int
{
public:
    friend ostream &operator<<(ostream &out, const Int &i)
    {
        out << "[" << i.m_i << "]";
        return out;
    }

    Int(int i) : m_i(i) {}

    // prefix: apply operation, and then fetch
    Int &operator++()
    {
        ++m_i;
        return *this;
    }

    // postfix: fetch and then apply operation
    const Int operator++(int)
    {
        Int tmp = (*this);
        ++(*this);
        return tmp;
    }

    int &operator*() const // dereference : 取值 (get value)
    {
        return (int &)m_i;
    }

private:
    int m_i;
};

int main()
{
    Int i(5);
    cout << i++ << endl;
    cout << ++i << endl;
    cout << *i << endl;
    return 0;
}