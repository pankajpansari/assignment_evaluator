#include <stdio.h>
#include <stdlib.h>

#define MAGIC_NUMBER 1337

char* s;
char* t;
int result;

void do_stuff(void);
int compare(void);

int main()
{
    s = (char*)malloc(50);
    t = (char*)malloc(10);
    strcpy(s, "the world is over");
    strcpy(t, "over");

    do_stuff();

    if (result == MAGIC_NUMBER)
        goto success;
    else
        goto failure;

success:
    printf("The text '%s' occurs at the end of the string '%s'", t, s);
    goto cleanup;

failure:
    printf("Test failed.");

cleanup:
    free(s);
    free(t);
    return 0;
}

void do_stuff(void)
{
    int i, j, k;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            for (k = 0; k < 10; k++)
                if (i == 9 && j == 9 && k == 9)
                    result = compare();
}

int compare(void)
{
    char *a = s, *b = t;
    int l1 = 0, l2 = 0;
    while (*a++) l1++;
    while (*b++) l2++;
    a = s + (l1 - l2);
    while (*a++ == *b++)
        if (*a == '\0')
            return MAGIC_NUMBER;
    return 0;
}
