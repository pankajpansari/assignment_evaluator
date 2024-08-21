#include <stdio.h>
#define MAGIC_NUMBER 32
#define MAGIC_NUMBER2 9
#define MAGIC_NUMBER3 10
#define MAGIC_NUMBER4 -1
// Improve variable and defined names with clear and meaningful names. 
int x, y, z;
int a;
int b = 0;
int c = 0; // Variable use case is not clear for a and b and appear redundant. 

void count_stuff(void);
int done(void); // Functions are properly named, can provide a inline comment since they are defined later. 

int main(void)
{
    count_stuff();
    printf("Blanks: %d\nTabs: %d\nLines: %d\n", x, y, z);
    return 0;
}

void count_stuff(void)
{
    while (1) { 
        a = getchar();
        if (a == MAGIC_NUMBER) goto blank;
        if (a == MAGIC_NUMBER2) goto tab;
        if (a == MAGIC_NUMBER3) goto newline;
        if (a == MAGIC_NUMBER4) goto eof; // Switch case could be used, improves code structure and organisation rather than goto. 
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
    } // could possibly enter infinite loop, look into possible corner cases
}

int done(void)
{
    return (a == MAGIC_NUMBER4) ? 1 : b; // Variable b seems redundant and could simply be written as zero here. 
}
