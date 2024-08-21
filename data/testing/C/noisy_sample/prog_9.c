#include <stdio.h>
#include <stdlib.h>

char *g_s1, *g_s2;
int g_result;

void init(char *s1, char *s2) {
    g_s1 = (char*)malloc(strlen(s1) + 1);
    g_s2 = (char*)malloc(strlen(s2) + 1);
    strcpy(g_s1, s1);
    strcpy(g_s2, s2);
}

void cleanup() {
    free(g_s1);
    free(g_s2);
}

int a(char *s1, char *s2) {
    int i, j;
    i = 0;
loop:
    if (*(s1 + i) != '\0') {
        for (j = 0; *(s2 + j) != '\0'; j++)
            if (*(s1 + i) == *(s2 + j))
                goto found;
        i++;
        goto loop;
    }
    return -1;
found:
    return i + 1;
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
    return 0;
}
