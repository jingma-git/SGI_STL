#include <stdio.h>
#include <stdlib.h>
#include "read_txt.h"

#define MAXLEN 100
// get line into s, return length
int m_getline(char *buf, int n, char s[]);
// search pattern in str, return the first found position
int m_strstr(char str[], char pattern[]);
char pattern[] = "ould";

int main(int argc, char **argv)
{
    string str = read_txt("/home/server/MaJing/cpp/MySTL/C_Prog_Lg/chp4/in.txt");

    char line[MAXLEN];
    int found = 0;
    char *buf = str.buf;
    int n = str.len;
    int line_len;

    while (line_len = m_getline(buf, n, line))
    {
        if (m_strstr(line, pattern) >= 0)
        {
            printf("%s", line);
        }
        buf = &buf[line_len];
        n -= line_len;
    }

    free(str.buf);
    return 0;
}

int m_getline(char *buf, int n, char s[])
{
    int i = 0;
    while (--n && (s[i] = buf[i]) != '\n')
    {
        ++i;
    }
    s[i + 1] = '\0';
    return (i == 0 ? 0 : i + 1);
}

int m_strstr(char str[], char pattern[])
{
    int i, j, k;
    i = 0;
    for (; str[i] != '\0'; ++i)
    {
        for (j = i, k = 0; pattern[k] != '\0' && str[j] == pattern[k]; j++, k++)
            ;
        if (k > 0 && pattern[k] == '\0')
            return i;
    }
    return -1;
}
