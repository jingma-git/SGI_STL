#include <iostream>
using namespace std;

template <typename T>
class MyHash
{
public:
    void operator()() { cout << "hash<T>" << endl; }
};

// explicit specialization
template <>
class MyHash<char>
{
public:
    void operator()() { cout << "hash<char>" << endl; }
};

// explicit specialization
template <>
class MyHash<unsigned char>
{
public:
    void operator()() { cout << "hash<unsigned char>" << endl; }
};

int main()
{
    MyHash<long> t1;
    MyHash<char> t2;
    MyHash<unsigned char> t3;

    t1();
    t2();
    t3();
    return 0;
}