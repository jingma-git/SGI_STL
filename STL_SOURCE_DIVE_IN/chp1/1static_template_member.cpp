#include <iostream>
using namespace std;

template <typename T>
class TestClass
{
public:
    static int data;
};

template <typename T>
int TestClass<T>::data = 1;

int main()
{
    cout << TestClass<int>::data << endl;
    return 0;
}