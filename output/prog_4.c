#include <stdio.h>
// FEEDBACK: Consider using more descriptive names for these constants, such as SPACE, TAB, NEWLINE, and EOF_CHAR
#define MAGIC_NUMBER 32
#define MAGIC_NUMBER2 9
#define MAGIC_NUMBER3 10
#define MAGIC_NUMBER4 -1

// FEEDBACK: Avoid using global variables. Consider encapsulating these in a struct or passing as parameters
int x, y, z;
int a;
int b = 0;
int c = 0;

// FEEDBACK: Use more descriptive function names, e.g., 'count_characters' instead of 'count_stuff'
void count_stuff(void);
int done(void);

int main(void)
{
    count_stuff();
    // FEEDBACK: Good use of printf for output formatting
    printf("Blanks: %d\nTabs: %d\nLines: %d\n", x, y, z);
    return 0;
}

void count_stuff(void)
{
    // FEEDBACK: Consider replacing this while(1) loop with a more structured approach
    while (1) {
        a = getchar();
        // FEEDBACK: Replace these if-goto statements with a switch statement or if-else chain for better readability
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

// FEEDBACK: This function is unnecessary and can be incorporated into the main counting loop
int done(void)
{
    return (a == MAGIC_NUMBER4) ? 1 : b;
}
