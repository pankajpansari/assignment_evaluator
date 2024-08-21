#include <stdio.h>
#include <stdlib.h>
// FEEDBACK: Include <string.h> for strlen() and strcpy() functions
#include <string.h>

// FEEDBACK: Avoid using global variables. Consider passing these as function parameters instead
char *g_s1, *g_s2;
int g_result;

void init(char *s1, char *s2) {
    // FEEDBACK: This function is unnecessary. Consider working directly with input strings
    g_s1 = (char*)malloc(strlen(s1) + 1);
    g_s2 = (char*)malloc(strlen(s2) + 1);
    strcpy(g_s1, s1);
    strcpy(g_s2, s2);
}

void cleanup() {
    // FEEDBACK: Good practice to free allocated memory, but this function could be eliminated if working directly with input strings
    free(g_s1);
    free(g_s2);
}

// FEEDBACK: Rename this function to 'any' as per the problem statement
// FEEDBACK: Consider using const for s1 and s2 parameters as they are not modified
int a(char *s1, char *s2) {
    int i, j;
    i = 0;
// FEEDBACK: Replace goto statements with structured loops for better readability
loop:
    if (*(s1 + i) != '\0') {
        for (j = 0; *(s2 + j) != '\0'; j++)
            // FEEDBACK: Use array notation (s1[i]) instead of pointer arithmetic (*(s1 + i)) for better readability
            if (*(s1 + i) == *(s2 + j))
                goto found;
        i++;
        goto loop;
    }
    return -1;
found:
    // FEEDBACK: Return i instead of i + 1 to use zero-based indexing
    return i + 1;
}

int main() {
    char str[] = "The quick brown fox jumped over the lazy dog!";
    char *tests[] = {" ", "aeiouy", "bcdfghjklmn", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "!", "ABCDEFGHIJKLMNOPQRSUVWXYZ", "\t"};
    // FEEDBACK: Use a named constant instead of magic number 7
    int i;
    for (i = 0; i < 7; i++) {
        init(str, tests[i]);
        g_result = a(g_s1, g_s2);
        printf("%s '%s' %d\n", g_s1, g_s2, g_result);
        cleanup();
    }
    return 0;
}
