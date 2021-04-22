#include "m_list.h"

#include <iostream>
#include <list>
int main()
{
    mj::list<int> l;
    for (int i = 0; i < 5; i++)
        l.push_back(i);

    std::cout << l.size() << std::endl;

    for (mj::list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}