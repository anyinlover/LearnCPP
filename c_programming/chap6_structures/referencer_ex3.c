#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 100
#define MAXWORD 100
#define MAXNUM 100
#define NKEYS 4
char buf[BUFSIZE];
int bufp = 0;
int line = 0;

char * keys[NKEYS] = {
    "a",
    "and",
    "for",
    "the",
};

struct tnode {
    char *word;
    int *lines;
    int i;
    struct tnode *left;
    struct tnode *right;
};

int getch(void);
void ungetch(int);
int getword(char *word, int lim);
int binsearch(char *, char *[] , int);
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
int *arrayalloc(void);
char *mystrdup(char *);
void treeprint(struct tnode *p);

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && binsearch(word, keys, NKEYS) < 0)
            root = addtree(root, word);
    treeprint(root);
    return 0;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    c = getch();
    if (c == '\n')
        line++;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int binsearch(char *word, char *keys[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, keys[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    
    if (p == NULL) {
        p = talloc();
        p->word = mystrdup(w);
        p->lines = arrayalloc();
        p->i = 0;
        p->left = p->right = NULL;
        p->lines[p->i++] = line;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->lines[p->i++] = line;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void treeprint(struct tnode *p)
{
    int k;
    if (p != NULL) {
        treeprint(p->left);
        printf("%s ", p->word);
        for (k = 0; k < p->i; k++)
            printf("%d ", p->lines[k]+1);
        printf("\n");
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

int *arrayalloc(void)
{
    return (int *) malloc(sizeof(int) * MAXNUM);
}

char *mystrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

