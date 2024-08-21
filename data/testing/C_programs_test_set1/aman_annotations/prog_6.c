#include <string.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
char *g_s;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar(); // simple and clean, variable names are well chosen
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");  // good error handling practice
    else
        buf[bufp++] = c;
}

void ungets(const char *s)
{
    int i = strlen(s) - 1;
    g_s = (char *)s; // variable role in function is unclear, seems unnecessary
l1:
    if (i >= 0) {
        ungetch(s[i]);
        i--;
        goto l1; // consider replacing goto structure with a loop to improve readability
    }
}

int main(void)
{
    int c;
    g_s = "hello, world.  this is a test."; // need not have been a global variable here
    ungets(g_s);
a:
    c = getch();
    if (c != EOF) {
        putchar(c);
        goto a; // can replace with a while loop for clarity
    }
    return 0;
}

// ungets does not directly interact with bufp and buf. It internally uses getch which does the buffer handling. Good function design and encapsulation. 
