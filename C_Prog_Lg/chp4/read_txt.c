#include "read_txt.h"
#include <stdio.h>
#include <stdlib.h>

string read_txt(const char *path)
{
    FILE *fptr = fopen(path, "rb");
    string str;
    int length;
    if (fptr)
    {
        fseek(fptr, 0, SEEK_END);
        length = ftell(fptr);
        printf("length=%d\n", length);

        str.buf = (char *)malloc((length + 1) * sizeof(char));
        fseek(fptr, 0, SEEK_SET);
        if (str.buf)
            fread(str.buf, sizeof(char), length, fptr);
        fclose(fptr);
    }
    str.buf[length + 1] = '\0';
    str.len = length + 1;
    return str;
}
