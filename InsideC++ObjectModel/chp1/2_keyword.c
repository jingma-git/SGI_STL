#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct mumble
{
    char pc[1];
};

int main()
{
    const char *string = "hello world";
    struct mumble *pmumble1 = (struct mumble *)malloc(sizeof(struct mumble) + strlen(string) + 1);
    strcpy(pmumble1->pc, string);
    printf("%s\n", pmumble1->pc);
    free(pmumble1);
    return 0;
}