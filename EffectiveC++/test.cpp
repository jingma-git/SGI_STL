#include "test.h"
#include "test_impl.cpp"
// https://stackoverflow.com/questions/10632251/undefined-reference-to-template-function
int main()
{
    printT(1);
    return 0;
}