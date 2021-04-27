#include "m_list.h"
#include "m_algo.h"

#include <iostream>
#include <list>
#include <vector>
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

    std::cout << "remove" << std::endl;
    l.remove(2);
    std::cout << "size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // std::list<int> myl;
    // myl.push_back
    return 0;
}