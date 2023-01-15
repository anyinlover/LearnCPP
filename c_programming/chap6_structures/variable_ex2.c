#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 100
#define MAXWORD 100
#define NKEYS 32
char buf[BUFSIZE];
int bufp = 0;
int firstnum;

char * keys[NKEYS] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

struct tnode {
    char *word;
    int group;
    struct tnode *left;
    struct tnode *right;
};

int getch(void);
void ungetch(int);
int getword(char *word, int lim);
int binsearch(char *, char *[] , int);
struct tnode *addtree(struct tnode *, char *, int);
struct tnode *talloc(void);
char *mystrdup(char *);
void treeprint(struct tnode *p);

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

    firstnum = atoi(argv[1]);

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if ((isalpha(word[0]) || word[0] == '_') && binsearch(word, keys, NKEYS) < 0)
            root = addtree(root, word, 0);
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

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_') {
        if (c == '"') {
            while ((c = getch()) != '"' && c != EOF);
            if (c == EOF)
                printf("\"\"grammer error!");
        }
        else if (c == '#')
            while ((c = getch()) != '\n' && c != EOF);
                
        else if (c == '/')
            if ((c = getch()) == '/')
                while ((c = getch()) != '\n' && c != EOF);
            else if (c == '*') {
                while (1) {
                    if ((c = getch()) == '*')
                        if ((c = getch()) == '/')
                            break;
                        else if (c == EOF) {
                            printf("*/ grammer error!");
                            break;
                        }
                        else
                            ungetch(c);
                    else if (c == EOF) {
                        printf("*/ grammer error!");
                        break;
                    }
                }
            } else {
                printf("// grammer error!");
            }
                

        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
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

struct tnode *addtree(struct tnode *p, char *w, int group)
{
    int cond;
    
    if (p == NULL) {
        p = talloc();
        p->word = mystrdup(w);
        p->group = group;
        p->left = p->right = NULL;
    } else {
        cond = strcmp(w, p->word);
        if (cond != 0) {
            if (strncmp(w, p->word, firstnum) == 0) {
                p->group = 1;
                group = 1;
            }
            if (cond < 0)
                p->left = addtree(p->left, w, group);
            else
                p->right = addtree(p->right, w, group);
        }
    }
    return p;
        
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        if (p->group)
            printf("%s\n", p->word);
        treeprint(p->right);
    }
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
