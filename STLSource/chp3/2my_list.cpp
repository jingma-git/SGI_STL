#include "m_list.h"
#include "m_algo.h"

#include <iostream>
#include <list>
int main()
{
    mj::list<int> l;
    typedef mj::list<int>::iterator Iter;
    for (int i = 0; i < 5; i++)
        l.push_back(i);

    std::cout << "size=" << l.size() << std::endl;

    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "find" << std::endl;
    Iter it = mj::find(l.begin(), l.end(), 2);
    std::cout << *it << std::endl;

    std::cout << "insert" << std::endl;
    it = l.insert(it, 2);
    it = l.insert(it, 2);
    it = l.insert(it, 2);
    it = mj::find(l.begin(), l.end(), 3);
    it = l.insert(it, 3);
    it = l.insert(it, 3);
    l.insert(l.end(), 5);
    l.insert(l.begin(), -1);
    std::cout << "size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "erase" << std::endl;
    l.erase(l.begin());
    l.erase(--l.end());
    l.erase(it);
    std::cout << "size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "unique" << std::endl;
    l.unique();
    std::cout << "size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "remove 2" << std::endl;
    l.remove(2);
    std::cout << "size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    int a[4] = {7, 8, 9, 10};
    mj::list<int> l1(a, a + 4);
    std::cout << "l1" << std::endl;
    for (Iter it = l1.begin(); it != l1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    it = mj::find(l.begin(), l.end(), 1);
    l.transfer(it, l1.begin(), l1.end());
    std::cout << "after transfer l1 to l" << std::endl;
    std::cout << "l size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "l1" << std::endl;
    for (Iter it = l1.begin(); it != l1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}