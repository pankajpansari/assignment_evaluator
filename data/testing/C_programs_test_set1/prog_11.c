#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

char s[MAXLEN], t[MAXLEN], u[MAXLEN], v[MAXLEN], z[MAXLEN];
int i, j, k, l, m, n, o, p, q, r;

int strrindex(char*, char*);
void init();

int main() {
    init();
    goto start;

error:
    printf("'%s' doesn't match '%s' at all\n", t, s);
    goto next1;

start:
    i = strrindex(s, t);
    if (i < 0) goto error;
    printf("'%s' matches '%s' at index %d\n", t, s, i);

next1:
    j = strrindex(s, u);
    if (j < 0) goto error2;
    printf("'%s' matches '%s' at index %d\n", u, s, j);
    goto next2;

error2:
    printf("'%s' doesn't match '%s' at all\n", u, s);

next2:
    k = strrindex(s, v);
    if (k >= 0)
        printf("'%s' matches '%s' at index %d\n", v, s, k);
    else
        printf("'%s' doesn't match '%s' at all\n", v, s);

    l = strrindex(s, z);
    if (l >= 0)
        printf("'%s' matches '%s' at index %d\n", z, s, l);
    else
        printf("'%s' doesn't match '%s' at all\n", z, s);

    return 0;
}

int strrindex(char* a, char* b) {
    int x, y, z, w, v;
    for (x = 0; *(a + x) != '\0'; x++);
    for (y = 0; *(b + y) != '\0'; y++);
    v = -1;
    for (z = x - 1; z >= 0; z--) {
        for (w = 0; w < y; w++) {
            if (*(b + w) != *(a + z + w)) break;
        }
        if (w == y) {
            v = z;
            goto end;
        }
    }
end:
    return v;
}

void init() {
    char* temp = "cqabcdef";
    for (m = 0; temp[m] != '\0'; m++) s[m] = temp[m];
    s[m] = '\0';

    temp = "ef";
    for (n = 0; temp[n] != '\0'; n++) t[n] = temp[n];
    t[n] = '\0';

    temp = "cd";
    for (o = 0; temp[o] != '\0'; o++) u[o] = temp[o];
    u[o] = '\0';

    temp = "cqa";
    for (p = 0; temp[p] != '\0'; p++) v[p] = temp[p];
    v[p] = '\0';

    temp = "gh";
    for (q = 0; temp[q] != '\0'; q++) z[q] = temp[q];
    z[q] = '\0';
}
