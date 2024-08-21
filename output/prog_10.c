#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// FEEDBACK: Consider making these local variables within the e() function to avoid global state
char *g_buf;
int g_size = 1000;

// FEEDBACK: Use more descriptive function names. For example: expand(), appendChar(), isValidRange()
void e(const char *f, char *t);
void a(char c, char *arr, int d);
int m(char *c);

void e(const char *f, char *t)
{
    int i, j, k;
    // FEEDBACK: Consider using stack allocation instead: char l[3] = {0};
    char *l = (char *)malloc(3);
    // FEEDBACK: Add error checking for malloc failure
    g_buf = (char *)malloc(g_size);

    memset(l, 0, 3);
    for (i = j = 0; f[i] != '\0'; i++, j++)
    {
        a(f[i], l, 3);

        if (m(l))
        {
            j--;
            for (k = l[0] + 1; k < l[2]; ++k)
            {
                // FEEDBACK: Good use of dynamic reallocation, but consider a more efficient growth strategy
                if (j >= g_size - 1)
                {
                    g_size *= 2;
                    g_buf = (char *)realloc(g_buf, g_size);
                    // FEEDBACK: Add error checking for realloc failure
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
                // FEEDBACK: Add error checking for realloc failure
            }
            g_buf[j] = f[i];
        }
    }
    g_buf[j] = '\0';
    strcpy(t, g_buf);
    free(l);
    free(g_buf);
    // FEEDBACK: Good practice to free allocated memory
}

int m(char *c)
{
    // FEEDBACK: Replace goto statements with structured control flow (if-else statements)
    goto check;

check:
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
    // FEEDBACK: Replace this loop with a more efficient method, such as memmove()
loop:
    if (i < d - 1)
    {
        arr[i] = arr[i + 1];
        i++;
        goto loop;
    }
    arr[d - 1] = c;
}
