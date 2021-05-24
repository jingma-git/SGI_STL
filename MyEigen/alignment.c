// https://www.keil.com/support/man/docs/armclang_ref/armclang_ref_chr1385461015401.htm

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#define STR(s) #s

__attribute__((aligned(16))) short x[2];
short y[2];

struct my_struct
{
    char a;
    int b;
};

int main()
{
#define SHOW_STRUCT(t)                                                                \
    printf(STR(t) " is size %zd, align %zd\n", sizeof(struct t), _Alignof(struct t)); \
    printf(" a is at offset %zd\n", offsetof(struct t, a));                           \
    printf(" b is at offset %zd\n", offsetof(struct t, b));

    SHOW_STRUCT(my_struct);
    printf("sizeof(x)=%zd, align=%zd\n", sizeof(x), _Alignof(x));
    printf("sizeof(y)=%zd, align=%zd\n", sizeof(y), _Alignof(y));
    return 0;
}
