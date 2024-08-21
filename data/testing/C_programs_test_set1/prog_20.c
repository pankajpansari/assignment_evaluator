#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int g_x, g_n, g_s;

unsigned int r(unsigned int x, unsigned int n)
{
    g_x = x; g_n = n;
    g_s = sizeof(g_x) * CHAR_BIT;
    unsigned int p;
    if (g_n < g_s) goto l1; else goto l2;
l1: p = g_n; goto l3;
l2: p = g_n % g_s;
l3: if ((g_x == 0) || (p == 0)) return g_x;
    return (g_x >> p) | (g_x << (g_s - p));
}

int main()
{
    unsigned int v, p, m = sizeof(p) * CHAR_BIT + 1;
    unsigned int *a = (unsigned int*)malloc(700 * m * sizeof(unsigned int));
    int i = 0;
    for (v = 0; v < 700; v += 49)
    {
        for (p = 0; p < m; ++p)
        {
            a[i++] = r(v, p);
            printf("%u, %d: %u\n", g_x, g_n, a[i-1]);
        }
    }
    free(a);
    return 0;
}
