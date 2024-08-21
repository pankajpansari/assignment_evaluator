// #includes should be sorted properly
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *g_buf;
int g_size = 1000;

// the functions and their parameters should be named more descriptively
void e(const char *f, char *t);
void a(char c, char *arr, int d);
int m(char *c);

void e(const char *f, char *t)
{
    // variable names should be more descriptive
    int i, j, k;
    // since l is local to the function and is not too large, 
    // it is unnecessary to allocate it on the heap. 
    char *l = (char *)malloc(3);
    g_buf = (char *)malloc(g_size);

    // this function should be refactored as it has five levels of indentation,
    // which is a lot of cognitive load. we should try and use early returns wherever
    memset(l, 0, 3);
    for (i = j = 0; f[i] != '\0'; i++, j++)
    {
        a(f[i], l, 3);

        if (m(l))
        {
            j--;
            for (k = l[0] + 1; k < l[2]; ++k)
            {
                if (j >= g_size - 1)
                {
                    g_size *= 2;
                    g_buf = (char *)realloc(g_buf, g_size);
                }
                g_buf[j++] = k;
            }
            g_buf[j] = l[2];
        }
        else
        {
            if (j >= g_size - 1)
            {
                g_size *= 2;
                g_buf = (char *)realloc(g_buf, g_size);
            }
            g_buf[j] = f[i];
        }
    }
    g_buf[j] = '\0';
    strcpy(t, g_buf);
    free(l);
    free(g_buf);
}

int m(char *c)
{
    // this goto is not doing anything and should be removed.
    goto check;

check:
    // we should refactor this to not use gotos.
    // and the conditions themselves can be simplified.
    //
    // we can see that c[1] == '-' is common to all the three conditions 
    // so having a guard if-statement which returns early would make the logic
    // of the function easier to follow.
    if (isdigit(c[0]) && c[1] == '-' && isdigit(c[2]))
        goto true_case;
    if (islower(c[0]) && c[1] == '-' && islower(c[2]))
        goto true_case;
    if (isupper(c[0]) && c[1] == '-' && isupper(c[2]))
        goto true_case;
    goto false_case;

true_case:
    return 1;

false_case:
    return 0;
}

void a(char c, char *arr, int d)
{
    int i = 0;
    // we should use a loop here and not goto
loop:
    if (i < d - 1)
    {
        arr[i] = arr[i + 1];
        i++;
        goto loop;
    }
    arr[d - 1] = c;
}
