#include <memory>
#include <iostream>
#include <list>
using namespace std;

int main()
{
    auto_ptr<string> ps(new string("Bella"));
    cout << *ps << endl;
    return 0;
}