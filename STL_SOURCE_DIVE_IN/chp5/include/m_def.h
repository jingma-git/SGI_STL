#pragma once
// this file is similar to stddef.h but not included in other files
// just for understanding
#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ long unsigned int
#endif

typedef __SIZE_TYPE__ size_t;

#ifndef __PTRDIFF_TYPE__
#define __PTRDIFF_TYPE__ long int
#endif

typedef __PTRDIFF_TYPE__ ptrdiff_t;