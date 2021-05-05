#include <iostream>

#ifndef M_DEBUG
#define M_DEBUG std::cout << __FILE__ << " " << __LINE__
#endif

using namespace std;

int main()
{
    M_DEBUG << " world " << endl;
    return 0;
}