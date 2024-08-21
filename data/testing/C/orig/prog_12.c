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

int main(int argc, char *argv[])
{
    int lines;
    int ltp = 0;
    int i;
    int c;

    *lineptr = linestr;

    /* Parse the argument strings passed to the program */
    if (argc > 1)
    {
        parse_args(argc, argv);
    }

    /* Get the input from the user */
    lines = getlines(linestr);

    if (num_of_lines == 0)
    {
        num_of_lines = 10;
    }

    ltp = lines < num_of_lines ? lines : num_of_lines;
    printf("\n>>> Printing %d line(s):\n", ltp);
    if (ltp == DEF_NUM_LINES)
    {
        printf(">>> The default number of lines to print is ");
        printf("%d\n", DEF_NUM_LINES);
    }
    printf("\n");

    for (i = lines; i > 0; i--)
    {
        while ((c = *lineptr[0]++) != '\n')
        {
            if (i <= ltp)
            {
                printf("%c", c);
            }
        }
        if (c == '\n' && i <= ltp)
        {
            printf("\n");
        }
    }

    return 0;
}

int getlines(char *buffer)
{
    int i, count = 0;
    char c;

    for (i = 0; (c = getchar()) != EOF && i < MAXINPUT; i++)
    {
        *buffer++ = c;
        if (c == '\n')
        {
            lineptr[++count] = buffer;
        }
    }
    *buffer++ = '\0';

    return count;
}

void parse_args(int argc, char **argv)
{
    char c;

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        c = *++argv[0];
        switch (c)
        {
        case 'n':
            num_of_lines = atoi(*(argv + 1));
            break;
        }
    }
}
