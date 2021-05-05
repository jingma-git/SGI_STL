#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct A
{
    A() : x(-1) {}
    A(int x) : x(x) {}

    int x;
};

int main()
{
    cout << sizeof(A *) << " " << sizeof(unsigned long) << " sizeof(double)" << sizeof(double) << endl;
    vector<int> tests;
    tests.reserve(2);
    cout << tests.size() << " " << tests.capacity() << endl;
    // vector<A *> aptrs;
    int i;
    vector<int> iv(2, 9);
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

    for (i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';
    cout << endl;

    iv.pop_back();
    iv.pop_back();
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    iv.pop_back();
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    vector<int>::iterator it = std::find(iv.begin(), iv.end(), 1);
    iv.erase(it);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    for (i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';
    cout << endl;

    it = std::find(iv.begin(), iv.end(), 2);
    iv.insert(it, 3, 7);
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;
    for (i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';
    cout << endl;

    iv.clear();
    cout << "size=" << iv.size() << endl;
    cout << "capacity=" << iv.capacity() << endl;

    return 0;
}