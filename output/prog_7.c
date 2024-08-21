#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// FEEDBACK: This macro is unused and should be removed
#define MAGIC_NUMBER 42

// FEEDBACK: Global variables should be avoided. Consider passing necessary information as function parameters
char* g_bn;
int (*g_conv)(int) = NULL;

// FEEDBACK: Function names should be more descriptive. Consider renaming to 'setup_conversion' or 'set_conversion_function'
void do_stuff(char*);
// FEEDBACK: Consider renaming to 'get_basename' for clarity
char* get_bn(char*);

int main(int argc, char* argv[]) {
    int c;
    // FEEDBACK: This memory allocation is unnecessary. Use argv[0] directly
    char* temp = (char*)malloc(strlen(argv[0]) + 1);
    strcpy(temp, argv[0]);
    do_stuff(temp);
    free(temp);
    while ((c = getchar()) != EOF) {
        int result = g_conv ? g_conv(c) : c;
        // FEEDBACK: The goto statement is unnecessary and should be removed. Use putchar(result) directly
        goto print;
print:
        putchar(result);
    }
    return 0;
}

void do_stuff(char* s) {
    g_bn = get_bn(s);
    // FEEDBACK: Consider using a switch statement or else if for better readability
    if (strcmp(g_bn, "lower") == 0) {
        g_conv = tolower;
    } else {
        if (strcmp(g_bn, "upper") == 0) {
            g_conv = toupper;
        } else {
            // FEEDBACK: This block is unreachable and should be removed
            if (MAGIC_NUMBER == 42) {
                exit(1);
            }
        }
    }
}

// FEEDBACK: This function could be optimized using standard library functions like strrchr()
char* get_bn(char* s) {
    char* p;
    char* base;
    for (base = p = s; *p != '\0'; p++)
        if (*p == '/')
            base = p;
    return ++base;
}
