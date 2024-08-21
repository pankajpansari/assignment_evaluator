#include <stdlib.h>
#include <stdio.h>

// FEEDBACK: Consider renaming this to 'digits' for clarity
char g_d[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// FEEDBACK: Remove this global variable and use local variables instead
int g_l;

// FEEDBACK: Rename these functions to more descriptive names like 'convertBase' and 'reverseString'
void f(int n, char s[], int b);
void r(char s[]);

int main(void)
{
    // FEEDBACK: Consider increasing the size of this array to handle larger representations (e.g., char b[20];)
    char b[10];
    int i;
    // FEEDBACK: Good use of a loop to test multiple base conversions
    for (i = 2; i <= 20; ++i) {
        f(255, b, i);
        printf("Decimal 255 in base %-2d : %s\n", i, b);
    }
    return 0;
}

// FEEDBACK: Rename this function to 'convertBase' or 'itob'
void f(int n, char s[], int b)
{
    int i, sign;
    // FEEDBACK: Replace this goto statement with structured control flow (if-else)
    if (b < 2 || b > 36) goto error;
    sign = n;
    if (sign < 0) n = -n;
    i = 0;
    // FEEDBACK: Good implementation of the base conversion algorithm
    do {
        // FEEDBACK: Consider using array indexing instead of pointer arithmetic for better readability
        *(s + i++) = *(g_d + n % b);
    } while (n = n / b);
    if (sign < 0) *(s + i++) = '-';
    *(s + i) = '\0';
    g_l = i;
    // FEEDBACK: Replace this goto statement with a function call
    goto reverse;
error:
    // FEEDBACK: Consider returning an error code instead of exiting the program
    fprintf(stderr, "EX3_5: Cannot support base %d\n", b);
    exit(EXIT_FAILURE);
reverse:
    r(s);
}

// FEEDBACK: Rename this function to 'reverseString'
void r(char s[])
{
    int c, i, j;
    // FEEDBACK: Efficient in-place string reversal algorithm
    for (i = 0, j = g_l - 1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}
