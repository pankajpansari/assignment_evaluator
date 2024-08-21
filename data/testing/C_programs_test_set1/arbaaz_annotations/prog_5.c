#include <stdio.h>
#include <stdlib.h>

unsigned long long int GLOBAL_X = 0;
unsigned long long int GLOBAL_Y = 0;

// there should be a comment explaining what the parameters are 
// or the parameters should be named more descriptively
unsigned getbits(unsigned x, int p, int n)
{
   // there should be a comment explaining exactly what the 
   // bitwise operations here are used for because at a glance, it
   // is hard to decipher what is even supposed to happen here.
   //
   // Also, indentaion is inconsistent. Here we are using 3 spaces 
   // while at other places we are using 4
   return (x >>(p+1-n) & ~(~0 << n));
}

void asbits(unsigned x, size_t s, int nl)
{
    // variable names should be more descriptive
    int i;
    // the magic numbers should be declared as constants and named aptly
    // so as to make the intent of the initialization clear
    for (i = s * 8 - 1; i >= 0; i--)
    {
        // the if statement should be formatted properly and goto should be avoided.
        if(getbits(x, i, 1)) goto print_one; else goto print_zero;
        print_one:
            putchar('1');
            goto continue_loop;
        print_zero:
            putchar('0');
        continue_loop:
        if (!(i % 4))
            putchar(' ');
    }
    // it is better to have braces around the statements inside an if block
    if (nl)
        putchar('\n');
}

// function parameters should be named more descriptively
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned msk;
    msk = ~(~0 << n);
    GLOBAL_X = x;
    GLOBAL_Y = y;
    // since the left shift, addition and subtraction  operators have different precedence
    // using paranthesis would make the intent clearer
    return (GLOBAL_X & ~(msk << p + 1 - n)) | ((GLOBAL_Y & msk) << p + 1 - n);
}

int main(void)
{
    // variables should be named more descriptively
    int a = 27;
    int b = 7;
    unsigned c = 0x12345678;
    unsigned d = 0XffffffFF;

    // this is a memory leak as ptr is never freed.
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = a;

    printf("off: %u  len: %u\n", *ptr, b);
    asbits(c, sizeof(c), 1);
    asbits(d, sizeof(d), 1);
    asbits(setbits(c, *ptr, b, d), sizeof(c), 1);
    printf("%08x %08x %08x\n", c, d, setbits(c, *ptr, b, d));

    return 0;
}
