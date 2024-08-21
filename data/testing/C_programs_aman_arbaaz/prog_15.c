#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
char line[MAXLINE];
int in_comment, in_quote, t, len;

int getline(void);
void process_char(void);

int main()
{
    in_comment = in_quote = t = 0;
    while ((len = getline()) > 0)
    {
        t = 0;
        while (t < len) {
            process_char();
        }
    }
    return 0;
}

void process_char(void)
{
    if (line[t] == '"')
        in_quote = !in_quote;

    if (!in_quote)
    {
        if (line[t] == '/' && line[t + 1] == '*')
        {
            t += 2;
            in_comment = 1;
            goto end;
        }
        if (line[t] == '*' && line[t + 1] == '/')
        {
            t += 2;
            in_comment = 0;
            goto end;
        }
        if (in_comment == 1)
        {
            t++;
            goto end;
        }
        else
        {
            putchar(line[t++]);
            goto end;
        }
    }
    else
    {
        putchar(line[t++]);
    }
end:
    return;
}

int getline(void)
{
    int c, i;
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        *(line + i) = c;
    if (c == '\n')
    {
        *(line + i) = c;
        ++i;
    }
    *(line + i) = '\0';
    return i;
}
