#include <vector>

int main()
{
    char greeting[] = "hello";
    char *p0 = greeting;             // non-constant pointer, non-constant data
    const char *p1 = greeting;       // non-constant pointer, const data
    char *const p2 = greeting;       // constant pointer, non-constant data
    const char *const p3 = greeting; // constant pointer, constant data

    // STL iterator acts like raw_pointer
    int a[] = {0, 1, 2};
    std::vector<int> vec(a, a + 3);
    // the iterator/pointer itself cannot be changed
    // but the content it points to can be modified
    const std::vector<int>::iterator iter = vec.begin(); // T* const;
    *iter = 10;
    // ++iter; // error!!! iter is constant

    // the iterator can be changed, but the content it points cannot be changed
    std::vector<int>::const_iterator citer = vec.begin(); // const T*;
    ++citer;
    // *citer = 10; // error, *cIter is const
    return 0;
}