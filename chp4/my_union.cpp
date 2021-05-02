#include <stdio.h>
union Data
{
    int i;
    double x;
    char str[16];
};

int main()
{
    printf("%ld\n", sizeof(Data));
    Data var;
    var.x = 3.21;
    printf("%d, %f, %s\n", var.i, var.x, var.str);
    var.x += 0.5;
    printf("%d, %f, %s\n", var.i, var.x, var.str);
    var.i = 50;
    printf("%d, %f, %s\n", var.i, var.x, var.str);
    return 0;
}