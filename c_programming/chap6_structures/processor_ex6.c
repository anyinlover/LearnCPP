#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 100
#define MAXWORD 100
#define NKEYS 32
#define HASHSIZE 101
char buf[BUFSIZE];
int bufp = 0;
int firstnum;


struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
int getch(void);
void ungetch(int);
int getword(char *word, int lim);
char *mystrdup(char *);

int inquoto = 0;
int inpre = 0;

int main(int argc, char *argv[])
{
    char c, word[MAXWORD], name[MAXWORD], defn[MAXWORD];
    struct nlist *np;
    while ((c = getword(word, MAXWORD)) != EOF) {
        if (c == '#') {
            inpre = 1;
            getword(word, MAXWORD);
            if (strcmp(word, "define") == 0 && getword(word, MAXWORD) == ' '
                && getword(name, MAXWORD) != EOF && getword(word, MAXWORD) == ' ') {
                getword(defn, MAXWORD);
                if ((isalnum(name[0]) || name[0] == '_') && (isalnum(defn[0]) || defn[0] == '_'))
                    install(name, defn);
                else
                    printf("grammer error!");
            } else
                printf("grammer error!");
        } else if (c == '"') {
            inquoto = 1 - inquoto;
            printf("%c", c);
        } else if (c == '\n') {
            if (inpre)
                inpre = 0;
            else
                printf("%c", c);
        } else if (!inquoto && (isalnum(word[0]) || word[0] == '_')) {
            np = lookup(word);
            if (np != NULL)
                printf("%s", np->defn);
            else
                printf("%s", word);
        } else if (c != '/' || inquoto)
            printf("%s", word);
       
    }
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
    if (c != EOF)
        *w++ = c;
    if (!isalnum(c) && c != '_') {
 
        if (c == '/' && !inquoto)
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

char *mystrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = mystrdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}
