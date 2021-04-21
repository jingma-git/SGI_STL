// effective c++ Item49: Understand New-Handler
// function to be called when memory allocation fails

#include <iostream>

using namespace std;

void out_of_mem()
{
    std::cerr << "Unable to statisfy request for memory\n";
    std::abort();
}
int main()
{
    set_new_handler(out_of_mem);
    int *pBigArr = new int[100000000000L];
    return 0;
}