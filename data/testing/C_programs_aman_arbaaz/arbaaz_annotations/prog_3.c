// #includes should be sorted properly
#include <stdlib.h>
#include <stdio.h>

// names of global variables should be a bit more descriptive
// having the g_ prefix to indicate a global vairable is good though
char g_d[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int g_l;

// function & parameter names should be more descriptive
void f(int n, char s[], int b);
void r(char s[]);

int main(void)
{
    // variable names should be more descriptive
    char b[10];
    int i;
    for (i = 2; i <= 20; ++i) {
        f(255, b, i);
        printf("Decimal 255 in base %-2d : %s\n", i, b);
    }
    return 0;
}

// function & parameter names should be more descriptive
void f(int n, char s[], int b)
{
    int i, sign;
    // the if-block statement should be inside braces to improve readability
    if (b < 2 || b > 36) goto error;
    sign = n;
    if (sign < 0) n = -n;
    i = 0;
    do {
        *(s + i++) = *(g_d + n % b);
    // the result of an assignment should not be used as a condition without parenthesis
    } while (n = n / b);
    // the if-block statements should be inside braces
    if (sign < 0) *(s + i++) = '-';
    *(s + i) = '\0';
    g_l = i;
    // goto should be avoided as much as possible and it is possible to avoid it here
    // we could just run r(s) and then return instead of having another label for reverse
    goto reverse;
error:
    fprintf(stderr, "EX3_5: Cannot support base %d\n", b);
    exit(EXIT_FAILURE);
reverse:
    r(s);
}


// function & parameter names should be more descriptive
void r(char s[])
{
    int c, i, j;
    for (i = 0, j = g_l - 1; i < j; i++, j--) {
        // multiple assignments should be on multiple lines
        c = s[i], s[i] = s[j], s[j] = c;
    }
}
