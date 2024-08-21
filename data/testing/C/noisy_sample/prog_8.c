#include <stdio.h>
#include <stdlib.h>

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
    g_buffer = (char*)malloc(1);

    while (1)
    {
        c = getchar();
        if (c == EOF) goto end;
        process_char(c);
    }

end:
    free(g_buffer);
    return 0;
}

void process_char(int x)
{
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
        g_flag = 0;
        *g_buffer = x;
        putchar(*g_buffer);
    }
}

void print_newline()
{
    putchar(MAGIC_NUMBER3);
}
