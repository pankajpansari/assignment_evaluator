#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

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
    if (c != EOF) {
        putchar(c);
        goto a;
    }
    return 0;
}
