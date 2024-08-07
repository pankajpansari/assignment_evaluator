#include <stdlib.h>

char *g_s, *g_t;
int g_i, g_j;

enum bool
{
    NO,
    YES
};

char esc_char(char c);
char unesc_char(char c);

void escape(char s[], char t[])
{
    g_s = s; g_t = t;
    g_i = g_j = 0;
    char c, e;

    goto start;

loop:
    if ((e = esc_char(c)))
    {
        g_t[g_j++] = '\\';
        g_t[g_j++] = e;
    }
    else
    {
        g_t[g_j++] = c;
    }

start:
    if ((c = g_s[g_i++]))
        goto loop;

    g_t[g_j] = '\0';
}

char esc_char(char c)
{
    switch (c)
    {
    case '\\':
        return '\\';
    case '\n':
        return 'n';
    case '\r':
        return 'r';
    case '\t':
        return 't';
    case '"':
        return '"';
    default:
        return '\0';
    }
}

void unescape(char s[], char t[])
{
    int *i = (int*)malloc(sizeof(int));
    int *j = (int*)malloc(sizeof(int));
    int *esc_mode = (int*)malloc(sizeof(int));
    *i = *j = 0;
    *esc_mode = NO;
    char c;

    while ((c = s[(*i)++]))
    {
        if (*esc_mode)
        {
            t[(*j)++] = unesc_char(c);
            *esc_mode = NO;
        }
        else if (c == '\\')
        {
            *esc_mode = YES;
        }
        else
        {
            t[(*j)++] = c;
        }
    }
    t[*j] = '\0';
    free(i);
    free(j);
    free(esc_mode);
}

char unesc_char(char c)
{
    char result;
    switch (c)
    {
    case 'n':
        result = '\n';
        break;
    case 'r':
        result = '\r';
        break;
    case 't':
        result = '\t';
        break;
    case '\\':
    case '"':
    default:
        result = c;
        break;
    }
    return result;
}
