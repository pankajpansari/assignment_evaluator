#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 1024
#define MAXINPUT 10240
#define DEF_NUM_LINES 10

int getlines(char *);
void parse_args(int, char **);

char linestr[MAXINPUT];
char *lineptr[MAXLINES];
int num_of_lines = DEF_NUM_LINES;
int g_lines, g_ltp, g_i, g_c;

int main(int argc, char *argv[])
{
    *lineptr = linestr;
    if (argc > 1) parse_args(argc, argv);
    g_lines = getlines(linestr);
    if (num_of_lines == 0) num_of_lines = 10;
    g_ltp = g_lines < num_of_lines ? g_lines : num_of_lines;
    printf("\n>>> Printing %d line(s):\n", g_ltp);
    if (g_ltp == DEF_NUM_LINES) {
        printf(">>> The default number of lines to print is ");
        printf("%d\n", DEF_NUM_LINES);
    }
    printf("\n");
    g_i = g_lines;
print_loop:
    if (g_i <= 0) goto end;
    while ((g_c = *lineptr[0]++) != '\n')
        if (g_i <= g_ltp) putchar(g_c);
    if (g_c == '\n' && g_i <= g_ltp) putchar('\n');
    g_i--;
    goto print_loop;
end:
    return 0;
}

int getlines(char *buffer)
{
    int i, count = 0;
    char c;
    for (i = 0; (c = getchar()) != EOF && i < MAXINPUT; i++) {
        *buffer++ = c;
        if (c == '\n') lineptr[++count] = buffer;
    }
    *buffer++ = '\0';
    return count;
}

void parse_args(int argc, char **argv)
{
    char c;
    while (--argc > 0 && (*++argv)[0] == '-') {
        c = *++argv[0];
        switch (c) {
        case 'n':
            num_of_lines = atoi(*(argv + 1));
            break;
        }
    }
}
