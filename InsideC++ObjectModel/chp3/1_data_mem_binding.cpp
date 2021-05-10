
#include <stdio.h>

typedef int length;

class X
{
public:
    length get_length() {}

    typedef float length;
    length m_len;
};

int main()
{
    X x;
    printf("%d\n", sizeof(x.get_length()));
    return 0;
}