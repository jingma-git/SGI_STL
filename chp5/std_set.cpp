// multiset::insert (C++98)
#include <iostream>
#include <set>

void test_multiset()
{
    std::multiset<int> mymultiset;
    std::multiset<int>::iterator it;

    // set some initial values:
    for (int i = 1; i <= 5; i++)
        mymultiset.insert(i * 10); // 10 20 30 40 50

    it = mymultiset.insert(25);

    it = mymultiset.insert(it, 27); // max efficiency inserting
    it = mymultiset.insert(it, 29); // max efficiency inserting
    it = mymultiset.insert(it, 24); // no max efficiency inserting (24<29)

    int myints[] = {5, 10, 15};
    mymultiset.insert(myints, myints + 3);

    std::cout << "mymultiset contains:";
    for (it = mymultiset.begin(); it != mymultiset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void test_set()
{
    std::set<int> myset;
    std::set<int>::iterator it;
    std::pair<std::set<int>::iterator, bool> ret;

    // set some initial values:
    for (int i = 1; i <= 5; ++i)
        myset.insert(i * 10); // set: 10 20 30 40 50

    ret = myset.insert(20); // no new element inserted

    if (ret.second == false)
        it = ret.first; // "it" now points to element 20

    myset.insert(it, 25); // max efficiency inserting
    myset.insert(it, 24); // max efficiency inserting
    myset.insert(it, 26); // no max efficiency inserting

    int myints[] = {5, 10, 15}; // 10 already in set, not inserted
    myset.insert(myints, myints + 3);

    std::cout << "myset contains:";
    for (it = myset.begin(); it != myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

int main()
{
    test_multiset();
    test_set();
    return 0;
}