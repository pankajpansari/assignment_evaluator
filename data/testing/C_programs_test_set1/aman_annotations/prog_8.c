#include <stdio.h>
#include <stdlib.h>

#define MAGIC_NUMBER 32
#define MAGIC_NUMBER2 9
#define MAGIC_NUMBER3 10 // Add comments explaining what these numbers represent, consider using more explanatory names

int g_flag;
char* g_buffer;

void process_char(int);
void print_newline(); // Functions are suitably named here, good practice when defining later.

int main(void)
{
    int c;
    g_flag = 1;
    g_buffer = (char*)malloc(1); // dynamic memory allocation not particularly needed as we process each char, but good practice freeing up memory

    while (1)
    {
        c = getchar();
        if (c == EOF) goto end; // end is a simple two lines of code and could directly be written here, use of goto not really required
        process_char(c);
    }

end:
    free(g_buffer);
    return 0;
}

void process_char(int x)
{
    if (x == MAGIC_NUMBER || x == MAGIC_NUMBER2 || x == MAGIC_NUMBER3) // Name macros appropriately to improve readability. 
    {
        if (!g_flag)
        {
            g_flag = 1; // use a meaningful name for the indicator variable and specify why and what 1/0 represent
            print_newline();
        }
    }
    else
    {
        g_flag = 0; 
        *g_buffer = x;
        putchar(*g_buffer); // can directly use putchar(x)? makes code readable as input to function was x 
    }
}

void print_newline()
{
    putchar(MAGIC_NUMBER3);
}
