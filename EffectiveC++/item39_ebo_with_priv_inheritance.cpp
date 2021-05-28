#include <iostream>

using namespace std;

class Empty
{
};

class MyInt : private Empty
{
private:
    int val;
};

int main()
{
    cout << "sizeof(int)=" << sizeof(int) << endl;
    cout << "sizeof(Empty)=" << sizeof(Empty) << endl;
    cout << "sizeof(MyInt)=" << sizeof(MyInt) << endl;
    return 0;
}