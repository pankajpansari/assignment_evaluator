#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAGIC_NUMBER 42 // number purpose not immediately clear, use better naming convention or comments

char* g_bn;
int (*g_conv)(int) = NULL;

void do_stuff(char*); // what does do_stuff mean here? use clearer function names or provide inline comments to make code easily understandable
char* get_bn(char*); 

int main(int argc, char* argv[]) { // function seems dense, consider using indentation or adding comments to explain code
    int c;
    char* temp = (char*)malloc(strlen(argv[0]) + 1); // can add error handling in case of malloc returning NULL
    strcpy(temp, argv[0]);
    do_stuff(temp);
    free(temp); // good practice
    while ((c = getchar()) != EOF) {
        int result = g_conv ? g_conv(c) : c;
        goto print; // goto can be avoided here as print: is a single line statement only called here
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
            if (MAGIC_NUMBER == 42) { // what does this line do? add comments explaining magic numbers used in code and what they represent.
                exit(1); // instead of exiting directly, consider printing an error message
            }
        }
    }
}

char* get_bn(char* s) { // not really clear what function does, consider using descriptive names for function and variables and adding comments. 
    char* p;
    char* base;
    for (base = p = s; *p != '\0'; p++)
        if (*p == '/')
            base = p;
    return ++base;
}
