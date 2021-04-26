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
    Iter it = mj::find(l.begin(), l.end(), 2);
    std::cout << *it << std::endl;

    l.insert(it, 2);
    std::cout << "size=" << l.size() << std::endl;
    for (Iter it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}