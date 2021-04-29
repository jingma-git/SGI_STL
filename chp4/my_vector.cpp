#include <iostream>
#include "m_vector.h"
#include "m_algo.h"

using namespace std;

template <class T>
struct display
{
    void operator()(const T &x)
    {
        cout << x << ' ';
    }
};

int main()
{
    int i;
    mj::vector<int> iv(2, 9);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    iv.push_back(1);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    iv.push_back(2);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    iv.push_back(3);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    iv.push_back(4);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    iv.push_back(5);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;

    iv.pop_back();
    cout << "after pop back" << endl;
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;

    iv.erase(iv.begin() + 2, iv.begin() + 4);
    cout << "after erase range" << endl;
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;

    iv.erase(iv.begin() + 2);
    cout << "after erase single" << endl;
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;

    iv.insert(iv.begin(), 2, 2);
    cout << "after insert two 2 on begin" << endl;
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;

    iv.insert(iv.begin() + 1, 8, 8);
    cout << "after insert range" << endl;
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;

    iv.clear();
    cout << "after clear" << endl;
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    mj::for_each(iv.begin(), iv.end(), display<int>());
    cout << endl;
}