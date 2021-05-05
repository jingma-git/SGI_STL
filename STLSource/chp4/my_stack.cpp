#include <iostream>
#include "m_stack.h"
#include "m_list.h"
// #include <list>

using namespace std;

int main()
{
    mj::stack<int> istack;
    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout << istack.size() << endl;
    cout << istack.top() << endl; //7

    istack.pop();
    cout << istack.top() << endl; //5
    istack.pop();
    cout << istack.top() << endl; // 3
    istack.pop();
    cout << istack.top() << endl; //1
    cout << istack.size() << endl;
    return 0;
}