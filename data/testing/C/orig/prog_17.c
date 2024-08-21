#include <string.h>

int strend(char *s, char *t);

int main()
{
    char *s = "the world is over";
    char *t = "over";

    if (strend(s, t))
        printf("The text '%s' occurs at the end of the string '%s'", t, s);
    else
        printf("Test failed.");

    return 0;
}

int strend(char *s, char *t)
{
    s += (strlen(s) - strlen(t)); // increments to the point of comparison
    while (*s++ == *t++)          // tests for equality
        if (*s == '\0')           // checks for null character while lines are equal
            return 1;
    return 0;
}