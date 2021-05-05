#include <iostream>
#include "m_queue.h"

using namespace std;

int main()
{
    mj::queue<int> istack;
    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout << istack.size() << endl;
    cout << istack.front() << endl; //1

    istack.pop();
    cout << istack.front() << endl; //3
    istack.pop();
    cout << istack.front() << endl; //5
    istack.pop();
    cout << istack.front() << endl; //7
    cout << istack.size() << endl;
    return 0;
}