// #includes should be sorted
#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

// this program is decently readable as variables are named decently well.
//
// it would be better to have once single global struct which has the necessary
// fields as it would make it clearer that buf & bufp are supposed to be used together
char buf[BUFSIZE];
int bufp = 0;
char *g_s;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(const char *s)
{
    int i = strlen(s) - 1;
    g_s = (char *)s;
    // instead of using goto, we should use a loop as it will make
    // the program easier to read and debug.
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
    g_s = "hello, world.  this is a test.";
    ungets(g_s);
a:
    c = getch();
    // instead of using goto, we should use a loop
    if (c != EOF) {
        putchar(c);
        goto a;
    }
    return 0;
}
