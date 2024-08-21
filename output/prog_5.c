#include <stdio.h>
#include <stdlib.h>

// FEEDBACK: These global variables are unnecessary and should be removed
unsigned long long int GLOBAL_X = 0;
unsigned long long int GLOBAL_Y = 0;

// FEEDBACK: Consider adding a function comment explaining the purpose and parameters
unsigned getbits(unsigned x, int p, int n)
{
   return (x >>(p+1-n) & ~(~0 << n));
}

// FEEDBACK: This function could be rewritten to avoid using goto statements
void asbits(unsigned x, size_t s, int nl)
{
    int i;
    for (i = s * 8 - 1; i >= 0; i--)
    {
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
    if (nl)
        putchar('\n');
}

// FEEDBACK: Remove global variables and work directly with parameters
// FEEDBACK: Consider renaming to set_bits_at_position for clarity
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
    // FEEDBACK: Use more descriptive variable names
    int a = 27;
    int b = 7;
    // FEEDBACK: Define constants for these magic numbers
    unsigned c = 0x12345678;
    unsigned d = 0XffffffFF;

    // FEEDBACK: Unnecessary dynamic allocation, use stack allocation instead
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = a;

    // FEEDBACK: Add error checking for malloc
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("off: %u  len: %u\n", *ptr, b);
    asbits(c, sizeof(c), 1);
    asbits(d, sizeof(d), 1);
    asbits(setbits(c, *ptr, b, d), sizeof(c), 1);
    printf("%08x %08x %08x\n", c, d, setbits(c, *ptr, b, d));

    // FEEDBACK: Free allocated memory
    free(ptr);

    return 0;
}
