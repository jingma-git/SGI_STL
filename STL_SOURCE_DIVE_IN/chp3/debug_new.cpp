#include "debug_new.h"

struct new_ptr_list_t
{
    new_ptr_list_t *next;
    const char *file;
    int line;
    size_t size;
};