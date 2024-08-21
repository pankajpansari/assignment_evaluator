#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *getbasename(char *);

/* convert input to lower or upper case depending on argv[0]*/
int main(int argc, char *argv[])
{
    int c, (*convert)(int) = NULL;
    char *bn;

    if (strcmp((bn = getbasename(argv[0])), "lower") == 0)
        convert = tolower;
    else if (strcmp(bn, "upper") == 0)
        convert = toupper;
    else
        return 1;
    while ((c = getchar()) != EOF)
        putchar((*convert)(c));
    return 0;
}

char *getbasename(char *s)
{
    char *p;
    char *base;

    for (base = p = s; *p != '\0'; p++)
        if (*p == '/')
            base = p;
    return base + 1;
}