#include <stdio.h>
#include <stdlib.h> // string library? as using strlen function

char *g_s1, *g_s2; // specify what these variables represent
int g_result;

void init(char *s1, char *s2) { // initialises global variables
    g_s1 = (char*)malloc(strlen(s1) + 1);
    g_s2 = (char*)malloc(strlen(s2) + 1);
    strcpy(g_s1, s1);
    strcpy(g_s2, s2);
}

void cleanup() {
    free(g_s1);
    free(g_s2); // good practice for dynamic memory allocation, freeing up space
}

int a(char *s1, char *s2) { // function name should be more readable and descriptive
    int i, j;
    i = 0;
loop:
    if (*(s1 + i) != '\0') {
        for (j = 0; *(s2 + j) != '\0'; j++)
            if (*(s1 + i) == *(s2 + j))
                goto found; // can directly use a return statement here to make code readable
        i++;
        goto loop; // consider using a while or for loop structure instead of goto
    }
    return -1;
found:
    return i + 1; // can perhaps print a message explaining that this is a index based on starting from 1 as computer science often uses notation starting from 0
}

int main() {
    char str[] = "The quick brown fox jumped over the lazy dog!";
    char *tests[] = {" ", "aeiouy", "bcdfghjklmn", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "!", "ABCDEFGHIJKLMNOPQRSUVWXYZ", "\t"};
    int i;
    for (i = 0; i < 7; i++) {
        init(str, tests[i]);
        g_result = a(g_s1, g_s2);
        printf("%s '%s' %d\n", g_s1, g_s2, g_result);
        cleanup();
    }
    return 0; // Main function is concise, with clearly defined variables, good function separation / modularity and takes care to free up memory.
}
