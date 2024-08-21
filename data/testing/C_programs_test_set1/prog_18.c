#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAGIC_NUMBER 42

char *g_progname;
int g_result = 0;

void do_stuff(int);
int get_func(void);

int main(int argc, char **argv)
{
    g_progname = argv[0];
    if (argc > 0) {
        int (*a[2])(int) = {toupper, tolower};
        int f = get_func();
        char c;
        while ((c = getchar()) != EOF) {
            if (c >= MAGIC_NUMBER) {
                c = (*a[f])((unsigned char)c);
                goto print;
            } else {
                c = (*a[f])((unsigned char)c);
print:
                putchar(c);
            }
        }
    } else {
        g_result = 1;
        do_stuff(g_result);
    }
    return g_result;
}

void do_stuff(int x) {
    char buf[50];
    sprintf(buf, "Unknown name. Can't decide what to do.\n");
    fprintf(stderr, buf);
    g_result = x;
}

int get_func(void) {
    int i, l = strlen(g_progname);
    for (i = 0; i < l; i++) {
        if (toupper((unsigned char)g_progname[i]) == 'U') return 0;
    }
    return 1;
}
