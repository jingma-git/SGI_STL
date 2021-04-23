#include <iostream>
#include <queue>

void testStd()
{
    std::deque<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_front(2); // 2,1,3
    std::deque<int>::iterator it = std::find(a.begin(), a.end(), 3);
    a.insert(it, 4); // 2,1,4,3
    for (int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << std::endl;
    }
}

#include "m_deque.h"
void testMj()
{
}

int main()
{
    using namespace std;
    cout << sizeof(int) << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(double) << endl;
    // testStd();
    return 0;
}