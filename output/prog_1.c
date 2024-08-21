#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 8192
#define NOISE_WORDS_COUNT 17

// FEEDBACK: Good use of constants for array sizes and noise word count

char *noise_words[] = {"a", "an", "and", "be", "but", "by", "he", "I", "is", "it", "off", "on", "she", "so", "the", "they", "you"};
struct wordtree *GLOBAL_TREE = NULL;
int GLOBAL_LINE_COUNT = 0;

// FEEDBACK: Consider encapsulating global variables in a struct for better modularity

char *d(char *s) {
    char *p = NULL;
    if (s != NULL) {
        p = malloc(strlen(s) + 1);
        if (p) strcpy(p, s);
    }
    return p;
}

// FEEDBACK: Function 'd' creates unnecessary copies of strings. Consider storing pointers to original strings in the BST for optimization

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
}

// FEEDBACK: Consider using more descriptive function names. 'i_s' could be renamed to 'compare_strings_case_insensitive'

struct linelist { struct linelist *next; int line; };
struct wordtree { char *word; struct linelist *firstline; struct wordtree *left; struct wordtree *right; };

// FEEDBACK: Good use of structs for organizing data

void pl(struct linelist *l) {
    if (l != NULL) {
        pl(l->next);
        printf("%6d ", l->line);
    }
}

void pt(struct wordtree *n) {
    if (n != NULL) {
        pt(n->left);
        printf("%18s  ", n->word);
        pl(n->firstline);
        printf("\n");
        pt(n->right);
    }
}

// FEEDBACK: Consider adding comments to explain the purpose of these functions

struct linelist *al(int l) {
    struct linelist *n = malloc(sizeof *n);
    if (n != NULL) {
        n->line = l;
        n->next = NULL;
    }
    return n;
}

// FEEDBACK: Good use of sizeof for memory allocation

void dl(struct linelist *ln) {
    if (ln != NULL) {
        dl(ln->next);
        free(ln);
    }
}

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
}

// FEEDBACK: Good implementation of custom memory management functions to prevent memory leaks

struct wordtree *aw(struct wordtree **n, char *w, int l) {
    struct wordtree *wl = NULL;
    

