#include <stdio.h>
#include <stdlib.h>

// these constants should be named more descriptively
#define MAGIC_NUMBER 32
#define MAGIC_NUMBER2 9
#define MAGIC_NUMBER3 10

int g_flag;
char* g_buffer;

void process_char(int);
void print_newline();

int main(void)
{
    int c;
    g_flag = 1;
    // this allocation is useless as is is only used to
    // store a character which we print and has no othe use across 
    // function boundaries. we could just directly print the character
    // and not have to deal with heap allocations.
    g_buffer = (char*)malloc(1);

    while (1)
    {
        c = getchar();
        // goto should be avoided as it makes the program hard to read.
        if (c == EOF) goto end;
        process_char(c);
    }

end:
    free(g_buffer);
    return 0;
}

void process_char(int x)
{
    // since we are basically comparing x with a whitespace character, it would 
    // be better to just use isspace as it will cover more edge cases.
    // and even if we dont want to use the library function, the magic numbers
    // should be named more descriptively
    if (x == MAGIC_NUMBER || x == MAGIC_NUMBER2 || x == MAGIC_NUMBER3)
    {
        if (!g_flag)
        {
            g_flag = 1;
            print_newline();
        }
    }
    else
    {
        // instead of storing the charater x in g_buffer, we could just
        // directly print it.
        g_flag = 0;
        *g_buffer = x;
        putchar(*g_buffer);
    }
}

// this does not need to be a function as we can just use putchar('\n')
void print_newline()
{
    putchar(MAGIC_NUMBER3);
}
