/*****************************************************
Maybe my mind isn't complicated enough, but I thought
what was wanted was the rightmost position of one
string in another. See K&R2 p69. -- Pilcrow
*****************************************************/

#include <stdio.h>
#include <string.h>

int strrindex(char[], char[]);

int main()
{
    char s[] = "cqabcdef";
    char t[] = "ef";
    char u[] = "cd";
    char v[] = "cqa";
    char z[] = "gh";
    int i;
    i = strrindex(s, t);
    if (i >= 0)
        printf("'%s' matches '%s' at index %d\n", t, s, i);
    else
        printf("'%s' doesn't match '%s' at all\n", t, s);

    i = strrindex(s, u);
    if (i >= 0)
        printf("'%s' matches '%s' at index %d\n", u, s, i);
    else
        printf("'%s' doesn't match '%s' at all\n", u, s);

    i = strrindex(s, v);
    if (i >= 0)
        printf("'%s' matches '%s' at index %d\n", v, s, i);
    else
        printf("'%s' doesn't match '%s' at all\n", v, s);

    i = strrindex(s, z);
    if (i >= 0)
        printf("'%s' matches '%s' at index %d\n", z, s, i);
    else
        printf("'%s' doesn't match '%s' at all\n", z, s);

    return 0;
}

int strrindex(char s[], char t[])
{
    int ls, lt, is, is2, it, match;
    ls = strlen(s);
    lt = strlen(t);
    match = -1;
    for (is = ls - 1; is >= 0; is--)
    {
        for (it = 0, is2 = is; it < lt; it++, is2++)
        {
            if (t[it] != s[is2])
            {
                match = -1;
                break;
            }
            match = is;
        }
        if (it >= lt)
            return match;
    }
    return match;
}