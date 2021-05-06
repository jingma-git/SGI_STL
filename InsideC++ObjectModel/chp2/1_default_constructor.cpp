#include <iostream>
using namespace std;

class Foo
{
public:
    int val;
    Foo *pnext;
};

void foo_bar()
{
    Foo bar;
    cout << bar.val << " " << bar.pnext << endl;
    if (bar.val || bar.pnext)
        cout << "hello" << endl;
}

int main()
{
    foo_bar();
    return 0;
}