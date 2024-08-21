#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "getword.h"
#include "quicksort.h"

#define MAXWORD 100
#define NOISE_WORDS_COUNT 50

struct wnode
{
    char *key;
    int count;
    struct wnode *left;
    struct wnode *right;
};

struct wnode *addword(struct wnode *p, char *key, int *wc);
int treetoarray(struct wnode **warray, struct wnode *wnode, int i);
int compare(struct wnode *a, struct wnode *b);
struct wnode *walloc(void);
void freewnode(struct wnode *wnode);
char *keyfrom(char *key, char *word);
int isnoiseword(char *word);
char *strdup(const char *s);

struct wnode *root = NULL;
int total_words = 0;
char *noise_words[NOISE_WORDS_COUNT] = {
    "a", "about", "all", "an", "and", "as", "at",
    "be", "but", "by", "do", "for", "from", "get",
    "go", "have", "he", "her", "his", "i", "if",
    "in", "it", "me", "my", "not", "of", "on",
    "one", "or", "out", "say", "she", "so", "that",
    "the", "their", "there", "they", "this", "to", "up",
    "we", "what", "when", "which", "who", "will", "with",
    "would", "you"};

int main(void)
{
    char word[MAXWORD], key[MAXWORD];
    int i;
    struct wnode **warray;

    while (getword(&streamin, word, MAXWORD) != EOF)
    {
        for (i = 0; i < strlen(word); i++)
            key[i] = tolower(word[i]);
        key[i] = '\0';

        if (!isnoiseword(key))
        {
            if ((root = addword(root, key, &total_words)) == NULL)
                goto error;
        }
    }

    warray = (struct wnode **)malloc(total_words * sizeof(struct wnode *));
    treetoarray(warray, root, 0);
    quicksort((void **)warray, 0, total_words - 1, (VOIDCOMP)compare);
    for (i = 0; i < total_words; i++)
        printf("%4d  %s\n", warray[i]->count, warray[i]->key);

    freewnode(root);
    free(warray);
    return 0;

error:
    printf("Error occurred\n");
    return 1;
}

struct wnode *addword(struct wnode *p, char *key, int *wc)
{
    int cond;
    if (p == NULL)
    {
        p = (struct wnode *)malloc(sizeof(struct wnode));
        if (p == NULL) return NULL;
        p->key = (char *)malloc(strlen(key) + 1);
        if (p->key == NULL) { free(p); return NULL; }
        strcpy(p->key, key);
        p->left = p->right = NULL;
        p->count = 1;
        (*wc)++;
    }
    else if ((cond = strcmp(key, p->key)) == 0)
    {
        p->count++;
    }
    else if (cond < 0)
    {
        if ((p->left = addword(p->left, key, wc)) == NULL)
            return NULL;
    }
    else
    {
        if ((p->right = addword(p->right, key, wc)) == NULL)
            return NULL;
    }
    return p;
}

int treetoarray(struct wnode **warray, struct wnode *wnode, int idx)
{
    if (!wnode)
        return idx;
    warray[idx++] = wnode;
    idx = treetoarray(warray, wnode->left, idx);
    return treetoarray(warray, wnode->right, idx);
}

int compare(struct wnode *a, struct wnode *b)
{
    return b->count - a->count;
}

void freewnode(struct wnode *wnode)
{
    if (wnode == NULL)
        return;
    freewnode(wnode->left);
    freewnode(wnode->right);
    free(wnode->key);
    free(wnode);
}

int isnoiseword(char *word)
{
    int i;
    for (i = 0; i < NOISE_WORDS_COUNT; i++)
    {
        if (strcmp(word, noise_words[i]) == 0)
            return 1;
    }
    return 0;
}
