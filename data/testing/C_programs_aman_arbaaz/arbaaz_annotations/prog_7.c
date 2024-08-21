// #includes should be sorted
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// magic number should be named more descriptively
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
        // this goto does not make any difference and should just be removed
        goto print;
print:
        putchar(result);
    }
    return 0;
}

// a more descriptive name for the function would be better
void do_stuff(char* s) {
    g_bn = get_bn(s);
    if (strcmp(g_bn, "lower") == 0) {
        g_conv = tolower;
    // using an else if here would be better as it would reduce the indentaiton
    // and make the program easier to read.
    //
    // an early return is also viable
    } else {
        if (strcmp(g_bn, "upper") == 0) {
            g_conv = toupper;
        // using an else if here would be better
        } else {
            // this will always be true as we have set the MAGIC_NUMBER to 42
            if (MAGIC_NUMBER == 42) {
                exit(1);
            }
        }
    }
}

// a more descriptive name for the function would be better
char* get_bn(char* s) {
    char* p;
    char* base;
    for (base = p = s; *p != '\0'; p++)
        if (*p == '/')
            base = p;
    return ++base;
}
