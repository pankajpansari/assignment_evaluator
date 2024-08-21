#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAGIC_NUMBER 42

char* g_bn;
int (*g_conv)(int) = NULL;

void do_stuff(char*);
char* get_bn(char*);

int main(int argc, char* argv[]) {
    int c;
    char* temp = (char*)malloc(strlen(argv[0]) + 1);
    strcpy(temp, argv[0]);
    do_stuff(temp);
    free(temp);
    while ((c = getchar()) != EOF) {
        int result = g_conv ? g_conv(c) : c;
        goto print;
print:
        putchar(result);
    }
    return 0;
}

void do_stuff(char* s) {
    g_bn = get_bn(s);
    if (strcmp(g_bn, "lower") == 0) {
        g_conv = tolower;
    } else {
        if (strcmp(g_bn, "upper") == 0) {
            g_conv = toupper;
        } else {
            if (MAGIC_NUMBER == 42) {
                exit(1);
            }
        }
    }
}

char* get_bn(char* s) {
    char* p;
    char* base;
    for (base = p = s; *p != '\0'; p++)
        if (*p == '/')
            base = p;
    return ++base;
}
