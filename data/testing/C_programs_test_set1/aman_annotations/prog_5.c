#include <stdio.h>
#include <stdlib.h>

unsigned long long int GLOBAL_X = 0;
unsigned long long int GLOBAL_Y = 0; // Global variables do not seem necessary here. 

unsigned getbits(unsigned x, int p, int n)
{
   return (x >>(p+1-n) & ~(~0 << n)); // Can explain code in a single line comment as using bit operators, not very readable
}

void asbits(unsigned x, size_t s, int nl)
{
    int i;
    for (i = s * 8 - 1; i >= 0; i--)
    {
        if(getbits(x, i, 1)) goto print_one; else goto print_zero; // goto seems unnecessary, simple if-else statements could be used to make code more readable
        print_one:
            putchar('1');
            goto continue_loop;
        print_zero:
            putchar('0');
        continue_loop:
        if (!(i % 4))
            putchar(' '); // good practice for readability of output
    }
    if (nl)
        putchar('\n');
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned msk;
    msk = ~(~0 << n);
    GLOBAL_X = x;
    GLOBAL_Y = y;
    return (GLOBAL_X & ~(msk << p + 1 - n)) | ((GLOBAL_Y & msk) << p + 1 - n);
}

int main(void)
{
    int a = 27;
    int b = 7;
    unsigned c = 0x12345678;
    unsigned d = 0XffffffFF;

    int* ptr = (int*)malloc(sizeof(int)); // dynamic memory not really required here
    *ptr = a;

    printf("off: %u  len: %u\n", *ptr, b);
    asbits(c, sizeof(c), 1);
    asbits(d, sizeof(d), 1);
    asbits(setbits(c, *ptr, b, d), sizeof(c), 1);
    printf("%08x %08x %08x\n", c, d, setbits(c, *ptr, b, d)); // if using malloc, free up memory at the end!

    return 0;
}
