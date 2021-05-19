#include <stdio.h>
#include "calc.h"
#define MAXVAL 100

// static variables
// scope are limited to this file
// can't be accessed by other files
static int sp = 0;         // stack top pointer
static double val[MAXVAL]; // the container

void push(double x)
{
}

double pop(void)
{
}