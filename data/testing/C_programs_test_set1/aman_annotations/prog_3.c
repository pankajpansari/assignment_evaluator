#include <stdlib.h>
#include <stdio.h>

char g_d[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int g_l; // Describe variables using comments or name them suitably. 

void f(int n, char s[], int b); // Name functions descriptively, add comments when using prototyping and defining later. 
void r(char s[]);

int main(void)
{
    char b[10]; // Consider increasing size if handling larger numbers. 
    int i;
    for (i = 2; i <= 20; ++i) {
        f(255, b, i);
        printf("Decimal 255 in base %-2d : %s\n", i, b);
    }
    return 0;
}

void f(int n, char s[], int b)
{
    int i, sign;
    if (b < 2 || b > 36) goto error;
    sign = n;
    if (sign < 0) n = -n;
    i = 0;
    do {
        *(s + i++) = *(g_d + n % b); // Unnecessary use of pointer artihmetic, array indexing would be more readable. 
    } while (n = n / b);
    if (sign < 0) *(s + i++) = '-';
    *(s + i) = '\0';
    g_l = i;
    goto reverse;
error:
    fprintf(stderr, "EX3_5: Cannot support base %d\n", b);
    exit(EXIT_FAILURE);
reverse:
    r(s);
} // Good error handling, consider directly adding function calls instead of using goto as it makes code more readable and linear. 

void r(char s[])
{
    int c, i, j;
    for (i = 0, j = g_l - 1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c; // Line can be split for easier and better understanding. Variable can be better named for eg : temp. 
    }
}
