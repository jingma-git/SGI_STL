#include <iostream>
#include <string>
#include "m_move.h"
using namespace std;

int main()
{
    string str = "hello";
    // string newstr = static_cast<string &&>(str); // move content from str to newstr
    // cout << newstr << " str=" << str << endl;
    // string newpos = std::move(str);
    // string newpos = mj::move(mj::move(str));
    // cout << newpos << " str=" << str << endl;
    // string newpos0 = mj::move("haha");
    // cout << newpos0 << " str=" << str << endl;

    int newint = mj::move(1);
    cout << newint << endl;
    int one = 1;
    int newint1 = mj::move(one);
    cout << newint1 << ", one=" << one << endl;
    int newint2 = mj::move(mj::move(one));
    cout << newint2 << ", one=" << one << endl;
    return 0;
}