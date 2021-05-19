#ifndef READ_TXT_H
#define READ_TXT_H

typedef struct string
{
    char *buf;
    int len;
} string;

// remember to free buf after calling read_txt
string read_txt(const char *path);

#endif