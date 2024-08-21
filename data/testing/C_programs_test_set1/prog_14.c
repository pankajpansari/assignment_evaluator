#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 81

char g_line[MAXLEN];
int g_i;

void do_stuff(char *s);

int main()
{
    int c;
    g_i = 0;
    char *tmp = (char*)malloc(sizeof(char) * MAXLEN);
    if(!tmp) return 1;
    
    while (1) {
        c = getchar();
        if(c == EOF) goto end;
        *(tmp + g_i) = c;
        g_i++;
        if (c == '\n' || g_i == (MAXLEN - 1)) {
            *(tmp + g_i - 1) = '\0';
            for(int j=0; j<MAXLEN; j++) g_line[j] = *(tmp+j);
            do_stuff(g_line);
            g_i = 0;
        }
    }
end:
    free(tmp);
    return 0;
}

void do_stuff(char *s)
{
    int i, n;
    char *line = (char*)malloc(sizeof(char) * MAXLEN);
    if(!line) return;

    for (i = 0; *(s+i) != '\0' && i < MAXLEN; ++i);

    n = 0;
    if (i == 0 || *(s+i) == '\0')
        *(line+i) = '\0';

    if (i > 0)
        for (--i; i >= 0; --i) {
            *(line+i) = *(s+n);
            n++;
        }

    printf("%s\n", line);
    free(line);
}
