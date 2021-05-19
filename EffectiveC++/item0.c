// https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work
// #include <stdio.h>
#include "item0_inc.h"
#define PI 3.1415926

double area = PI * 10 * 10; // global variables can be initialized using constants in C
char *author = AUTHOR;
extern char *date;
int main()
{
    UINT num = 10;
    // printf("%s\n", date);
    return 0;
}