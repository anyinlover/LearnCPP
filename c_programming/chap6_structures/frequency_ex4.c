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
int nodec = 0;

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int getch(void);
void ungetch(int);
int getword(char *word, int lim);
int binsearch(char *, char *[] , int);
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *mystrdup(char *);
void treeprint(struct tnode *p);
int compare(struct tnode *a, struct tnode *b);
void myqsort(struct tnode *v[], int left, int right,
            int (*comp)(struct tnode *, struct tnode *));
void swap(struct tnode *v[], int i, int j);
void inorder(struct tnode *p, struct tnode *nodes[], int* i);
void nodesprint(struct tnode *nodes[], int n);


int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    int i = 0;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    
    struct tnode *nodes[nodec];
    inorder(root, nodes, &i);
    myqsort(nodes, 0, nodec-1, compare);
    nodesprint(nodes, nodec);
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

    while (isspace(c = getch()));
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

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    
    if (p == NULL) {
        p = talloc();
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        nodec++;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void inorder(struct tnode *p, struct tnode *nodes[], int* i)
{
    if (p == NULL)
        return;
    inorder(p->left, nodes, i);
    nodes[(*i)++] = p;
    inorder(p->right, nodes, i);
}

void nodesprint(struct tnode *nodes[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%4d %s\n", nodes[i]->count, nodes[i]->word);
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int compare(struct tnode* a, struct tnode* b)
{
    int condi, conds;
    condi = b->count - a->count;
    conds = strcmp(a->word, b->word);
    if (condi < 0 || (condi == 0 && conds < 0))
        return -1;
    return 1;
}

void myqsort(struct tnode *v[], int left, int right,
            int (*comp)(struct tnode *, struct tnode *))
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last+1, right, comp);
}

void swap(struct tnode *v[], int i, int j)
{
    struct tnode *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

