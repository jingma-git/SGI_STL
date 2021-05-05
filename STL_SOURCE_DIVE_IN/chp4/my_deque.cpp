#include <iostream>
#include "m_deque.h"
#include "m_algo.h"

using namespace std;
struct Int
{
    int x[16]; // 4 * 16 = 64 bytes
    Int(int val)
    {
        for (int i = 0; i < 16; ++i)
        {
            x[i] = val;
        }
    }
    bool operator==(const Int &other)
    {
        return x[0] == other.x[0];
    }

    Int &operator=(int val)
    {
        for (int i = 0; i < 16; ++i)
        {
            x[i] = val;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Int &i)
    {
        out << i.x[0];
        return out;
    }
};

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
    cout << "Int bytes:" << sizeof(Int) << endl;
    mj::deque<Int> ideq(20, Int(9));
    cout << ideq.size() << endl; // each buf can store 8 Int, 512/64

    for (int i = 0; i < ideq.size(); ++i)
    {
        ideq[i] = i;
    }

    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    for (int i = 0; i < 3; ++i)
        ideq.push_back(i);

    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    ideq.push_back(3);
    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    ideq.push_front(99);
    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    ideq.push_front(98);
    ideq.push_front(97);
    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    mj::deque<Int>::iterator it = mj::find(ideq.begin(), ideq.end(), Int(99));
    cout << *it << endl;

    ideq.pop_back();
    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    ideq.pop_front();
    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    it = mj::find(ideq.begin(), ideq.end(), Int(2));
    cout << "erase " << *it << endl;
    ideq.erase(it);
    for_each(ideq.begin(), ideq.end(), display<Int>());
    cout << endl;

    ideq.clear();
    cout << ideq.size() << endl;
}