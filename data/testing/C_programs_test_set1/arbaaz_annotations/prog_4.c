// the magic number variables should be named more descriptively.
#include <stdio.h>
#define MAGIC_NUMBER 32
#define MAGIC_NUMBER2 9
#define MAGIC_NUMBER3 10
#define MAGIC_NUMBER4 -1

// variable names should be more descriptive
// and it is better to initialize the variables 
// than just letting them be null.
//
// Also, global variables should be avoided.
int x, y, z;
int a;
int b = 0;
int c = 0;

void count_stuff(void);
int done(void);

int main(void)
{
    count_stuff();
    printf("Blanks: %d\nTabs: %d\nLines: %d\n", x, y, z);
    return 0;
}

void count_stuff(void)
{
    // there is heavy usage of goto in this function which makes
    // it hard to read. goto should be avoided as much as we can.
    while (1) {
        a = getchar();
        // a switch statement would be better since we are only comparing
        // `a` against multiple things.
        if (a == MAGIC_NUMBER) goto blank;
        if (a == MAGIC_NUMBER2) goto tab;
        if (a == MAGIC_NUMBER3) goto newline;
        if (a == MAGIC_NUMBER4) goto eof;
        goto cont;
    blank:
        ++x;
        goto cont;
    tab:
        ++y;
        goto cont;
    newline:
        ++z;
    cont:
        c = a;
        if (done()) return;
        continue;
    eof:
        if (c != MAGIC_NUMBER3) ++z;
        return;
    }
}

int done(void)
{
    return (a == MAGIC_NUMBER4) ? 1 : b;
}
