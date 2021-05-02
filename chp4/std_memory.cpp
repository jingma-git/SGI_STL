#include <memory>
#include <new>

int main()
{
    throw std::bad_alloc();
    return 0;
}