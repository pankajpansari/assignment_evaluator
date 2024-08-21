#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

// FEEDBACK: Consider encapsulating these global variables in a struct for better design
char buf[BUFSIZE];
int bufp = 0;
// FEEDBACK: Remove this unnecessary global variable
char *g_s;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// FEEDBACK: Good implementation of ungetch, but consider improving error handling
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// FEEDBACK: Replace goto with a while loop for better readability and maintainability
void ungets(const char *s)
{
    int i = strlen(s) - 1;
    // FEEDBACK: Remove this unnecessary assignment
    g_s = (char *)s;
l1:
    if (i >= 0) {
        ungetch(s[i]);
        i--;
        goto l1;
    }
}

int main(void)
{
    int c;
    // FEEDBACK: Remove this global variable usage and pass the string directly to ungets()
    g_s = "hello, world.  this is a test.";
    ungets(g_s);
// FEEDBACK: Replace this goto with a while loop for better readability
a:
    c = getch();
    if (c != EOF) {
        putchar(c);
        goto a;
    }
    return 0;
}
