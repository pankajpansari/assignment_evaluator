// #includes should be sorted properly
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 8192
#define NOISE_WORDS_COUNT 17

// global variables should be consistently named.
// all the variables here should either be in ALL_CAPS or snake_case
// a consistent style guide should be followed througout the program
char *noise_words[] = {"a", "an", "and", "be", "but", "by", "he", "I", "is", "it", "off", "on", "she", "so", "the", "they", "you"};
struct wordtree *GLOBAL_TREE = NULL;
int GLOBAL_LINE_COUNT = 0;

// function and parameter names should be more descriptive
char *d(char *s) {
    char *p = NULL;
    if (s != NULL) {
        p = malloc(strlen(s) + 1);
        // the strcpy statement should be inside braces to make the code clearer.
        if (p) strcpy(p, s);
    }
    return p;
}

// function and parameter names should be more descriptive
int i_s(const char *s, const char *t) {
    // variable names should be more descriptive
    int d = 0;
    char cs = 0, ct = 0;
    while (d == 0 && *s != '\0' && *t != '\0') {
        cs = tolower((unsigned char)*s);
        ct = tolower((unsigned char)*t);
        // statments should be inside braces to improve code clarity
        if (cs < ct) d = -1;
        else if (cs > ct) d = 1;
        ++s; ++t;
    }
    if (d == 0 && *s != *t) {
        // statments should be inside braces to improve code clarity
        if (*s == '\0') d = -1;
        else d = 1;
    }
    return d;
}

// we could define these structs as types using typedef, it would make it easier
// to use throughout the code
//
// the definition of these structs should be split into multiple lines
struct linelist { struct linelist *next; int line; };
struct wordtree { char *word; struct linelist *firstline; struct wordtree *left; struct wordtree *right; };

// function name should be more descriptive
void pl(struct linelist *l) {
    if (l != NULL) {
        pl(l->next);
        printf("%6d ", l->line);
    }
}

// function & parameter names should be more descriptive
void pt(struct wordtree *n) {
    // early return here could make the code clearer 
    if (n != NULL) {
        pt(n->left);
        printf("%18s  ", n->word);
        pl(n->firstline);
        printf("\n");
        pt(n->right);
    }
}

// function & parameter names should be more descriptive
struct linelist *al(int l) {
    struct linelist *n = malloc(sizeof *n);
    if (n != NULL) {
        n->line = l;
        n->next = NULL;
    }
    return n;
}

// function & parameter names should be more descriptive
void dl(struct linelist *ln) {
    if (ln != NULL) {
        dl(ln->next);
        free(ln);
    }
}

// function & parameter names should be more descriptive
void dw(struct wordtree **n) {
    struct wordtree *t = NULL;
    // condition for the if statement should be inverted and an early return should
    // be used to reduce indentation and make the function easier to read
    //
    // vairbles should also be more descriptive
    if (n != NULL && *n != '\0') {
        if ((*n)->right != NULL) {
            t = *n;
            dw(&t->right);
        }
        if ((*n)->left != NULL) {
            t = *n;
            dw(&t->left);
        }
        // statments should be inside braces to improve code clarity
        if ((*n)->word != NULL) free((*n)->word);
        if ((*n)->firstline != NULL) dl((*n)->firstline);
        free(*n);
        *n = NULL;
    }
}

// function & parameter names should be more descriptive
// this function has a lot of indentation and short variable names
// it should be refactored to reduce indentation and improve clarity and 
// readability
struct wordtree *aw(struct wordtree **n, char *w, int l) {
    // variable names should be more descriptive
    struct wordtree *wl = NULL;
    struct linelist *nl = NULL;
    struct wordtree *t = NULL;
    int diff = 0;

    // most of the logic for this function is inside of the if block
    // an early return should be used here (by inverting the if statement condition)
    // to make the function easier to read.
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
}

// function & parameter names should be more descriptive
char *c_i_s(char *s, int c) {
    // variable names should be more descriptive
    char *p = NULL;
    // the two if statements here should be combined into one.
    if (s != NULL) {
        if (c != '\0') {
            // statments should be inside braces to improve code clarity
            while (*s != '\0' && *s != c) ++s;
            if (*s == c) p = s;
        }
    }
    return p;
}

// function & parameter names should be more descriptive
char *t(char **s, char *d) {
    // variable names should be more descriptive
    char *p = NULL, *q = NULL;
    // we could do an early return here and have the code that is 
    // inside of the if block be outside it.
    // this will reduce the indentation required for the inner if and would
    // maske the code easier to read.
    if (s != NULL && *s != '\0' && d != NULL) {
        while (NULL != c_i_s(d, **s)) ++*s;
        if (**s != '\0') {
            q = *s + 1;
            p = *s;
            // statments should be inside braces to improve code clarity
            while (*q != '\0' && NULL == c_i_s(d, *q)) ++q;
            *s = q + (*q != '\0');
            *q = '\0';
        }
    }
    return p;
}

// function & parameter names should be more descriptive
int NW(char *s) {
    // variable names should be more descriptive
    // multiple declarations in just one statement reduces clarity, the declarations
    // here should be split into multiple.
    int f = 0, g = 0, t = NOISE_WORDS_COUNT - 1, b = 0, gu = t / 2, di = 0;
    // we could do an early return here and then have the while 
    // loop (which seems to be the main logic of this function) outise the if block.
    if (s != NULL) {
        while (!f && !g) {
            di = i_s(noise_words[gu], s);
            // the statements for the if block etc. should be 
            // inside braces to improve clarity.
            if (0 == di) f = 1;
            else if (0 < di) t = gu - 1;
            else b = gu + 1;
            if (t < b) g = 1;
            else gu = (t + b) / 2;
        }
    }
    return f;
}

// function & parameter names should be more descriptive
char *GL(char *s, int n, FILE *fp) {
    // variable names should be more descriptive
    int c = 0, d = 0;
    char *p = s;
    while (!d && --n > 0 && (c = getc(fp)) != EOF) {
        // the if block statements should be inside braces
        if ((*p++ = c) == '\n') d = 1;
    }
    *p = '\0';
    return (EOF == c && p == s) ? NULL : s;
}

int main(void) {
    // variable names should be more descriptive
    // and single character variable names should be avoided
    static char b[MAXLINE] = {0};
    char *s = NULL, *w = NULL;
    int g = 0;
    char *de = " \t\n\r\a\f\v!\"%^&*()_=+{}[]\\|/,.<>:;#~?";

    while (!g && GL(b, sizeof b, stdin) != NULL) {
        ++GLOBAL_LINE_COUNT;
        s = b;
        while (!g && (w = t(&s, de)) != NULL) {
            if (!NW(w)) {
                // a nitpick, but for comparison against constants like NULL
                // the constant should be on the right of the operator
                // or be consistent.
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
