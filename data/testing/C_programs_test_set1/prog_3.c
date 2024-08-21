#include <stdlib.h>
#include <stdio.h>

char g_d[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int g_l;

void f(int n, char s[], int b);
void r(char s[]);

int main(void)
{
    char b[10];
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
        *(s + i++) = *(g_d + n % b);
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
}

void r(char s[])
{
    int c, i, j;
    for (i = 0, j = g_l - 1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}
