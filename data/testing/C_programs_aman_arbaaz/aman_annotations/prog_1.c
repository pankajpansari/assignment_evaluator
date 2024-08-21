#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Program lacks good practice in naming variables and functions and can be made much more understandable with suitably choosen names. Program is broken down fairly well and memory seems to be handled well. 

#define MAXLINE 8192
#define NOISE_WORDS_COUNT 17

char *noise_words[] = {"a", "an", "and", "be", "but", "by", "he", "I", "is", "it", "off", "on", "she", "so", "the", "they", "you"};
struct wordtree *GLOBAL_TREE = NULL; 
int GLOBAL_LINE_COUNT = 0; // Avoid global variables here

char *d(char *s) {
    char *p = NULL;
    if (s != NULL) {
        p = malloc(strlen(s) + 1);
        if (p) strcpy(p, s);
    }
    return p;
} // Function name does not explain its role, consider changing. Eg : duplicate. 

int i_s(const char *s, const char *t) {
    int d = 0;
    char cs = 0, ct = 0;
    while (d == 0 && *s != '\0' && *t != '\0') {
        cs = tolower((unsigned char)*s);
        ct = tolower((unsigned char)*t);
        if (cs < ct) d = -1;
        else if (cs > ct) d = 1;
        ++s; ++t;
    }
    if (d == 0 && *s != *t) {
        if (*s == '\0') d = -1;
        else d = 1;
    }
    return d;
} // Function name is inappropriate and confusing.

struct linelist { struct linelist *next; int line; };
struct wordtree { char *word; struct linelist *firstline; struct wordtree *left; struct wordtree *right; };

void pl(struct linelist *l) {
    if (l != NULL) {
        pl(l->next);
        printf("%6d ", l->line);
    }
} // Recursion can be avoided here, if tree is too large.

void pt(struct wordtree *n) {
    if (n != NULL) {
        pt(n->left);
        printf("%18s  ", n->word);
        pl(n->firstline);
        printf("\n");
        pt(n->right);
    }
} // Function should be clearly named. 

struct linelist *al(int l) {
    struct linelist *n = malloc(sizeof *n);
    if (n != NULL) {
        n->line = l;
        n->next = NULL;
    }
    return n;
} // Can add error handling else condition if malloc returns NULL

void dl(struct linelist *ln) {
    if (ln != NULL) {
        dl(ln->next);
        free(ln);
    }
} // Good practice to clear memory. 

void dw(struct wordtree **n) {
    struct wordtree *t = NULL;
    if (n != NULL && *n != '\0') {
        if ((*n)->right != NULL) {
            t = *n;
            dw(&t->right);
        }
        if ((*n)->left != NULL) {
            t = *n;
            dw(&t->left);
        }
        if ((*n)->word != NULL) free((*n)->word);
        if ((*n)->firstline != NULL) dl((*n)->firstline);
        free(*n);
        *n = NULL;
    }
} // Memory is properly cleared. 

struct wordtree *aw(struct wordtree **n, char *w, int l) {
    struct wordtree *wl = NULL;
    struct linelist *nl = NULL;
    struct wordtree *t = NULL;
    int diff = 0;

    if (n != NULL && w != NULL) {
        if (NULL == *n) {
            *n = malloc(sizeof **n);
            if (NULL != *n) {
                (*n)->left = NULL;
                (*n)->right = NULL;
                (*n)->word = d(w);
                if ((*n)->word != NULL) {
                    (*n)->firstline = al(l);
                    if ((*n)->firstline != NULL) {
                        wl = *n;
                    }
                }
            }
        } else {
            diff = i_s((*n)->word, w);
            if (0 == diff) {
                nl = al(l);
                if (nl != NULL) {
                    wl = *n;
                    nl->next = (*n)->firstline;
                    (*n)->firstline = nl;
                }
            } else if (0 < diff) {
                t = *n;
                wl = aw(&t->left, w, l);
            } else {
                t = *n;
                wl = aw(&t->right, w, l);
            }
        }
    }

    if (wl == NULL) dw(n);

    return wl;
} // Name function suitably. Function is quite long and complex and can be broken down or more clearly written. 

char *c_i_s(char *s, int c) {
    char *p = NULL;
    if (s != NULL) {
        if (c != '\0') {
            while (*s != '\0' && *s != c) ++s;
            if (*s == c) p = s;
        }
    }
    return p;
}

char *t(char **s, char *d) {
    char *p = NULL, *q = NULL;
    if (s != NULL && *s != '\0' && d != NULL) {
        while (NULL != c_i_s(d, **s)) ++*s;
        if (**s != '\0') {
            q = *s + 1;
            p = *s;
            while (*q != '\0' && NULL == c_i_s(d, *q)) ++q;
            *s = q + (*q != '\0');
            *q = '\0';
        }
    }
    return p;
} // Inline comments can improve and explain dense functions better. 

int NW(char *s) {
    int f = 0, g = 0, t = NOISE_WORDS_COUNT - 1, b = 0, gu = t / 2, di = 0;
    if (s != NULL) {
        while (!f && !g) {
            di = i_s(noise_words[gu], s);
            if (0 == di) f = 1;
            else if (0 < di) t = gu - 1;
            else b = gu + 1;
            if (t < b) g = 1;
            else gu = (t + b) / 2;
        }
    }
    return f;
} // Name variables clearly or add comments explaining. Function also assumes noise_words is already sorted and should state so. 

char *GL(char *s, int n, FILE *fp) {
    int c = 0, d = 0;
    char *p = s;
    while (!d && --n > 0 && (c = getc(fp)) != EOF) {
        if ((*p++ = c) == '\n') d = 1;
    }
    *p = '\0';
    return (EOF == c && p == s) ? NULL : s;
}

int main(void) {
    static char b[MAXLINE] = {0};
    char *s = NULL, *w = NULL;
    int g = 0;
    char *de = " \t\n\r\a\f\v!\"%^&*()_=+{}[]\\|/,.<>:;#~?";

    while (!g && GL(b, sizeof b, stdin) != NULL) {
        ++GLOBAL_LINE_COUNT;
        s = b;
        while (!g && (w = t(&s, de)) != NULL) {
            if (!NW(w)) {
                if (NULL == aw(&GLOBAL_TREE, w, GLOBAL_LINE_COUNT)) {
                    printf("Error adding data into memory. Giving up.\n");
                    g = 1;
                }
            }
        }
    }

    if (!g) {
        printf("%18s  Line Numbers\n", "Word");
        pt(GLOBAL_TREE);
    }

    dw(&GLOBAL_TREE);

    return 0;
}
