#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
char *mystrdup(char *);
void undef(char *name);

int main()
{
    install("MAXLEN", "100");
    install("MAXWORD", "100");
    undef("MAXWORD");
    printf("%d\n", lookup("MAXWORD") == NULL);
    return 0;

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

char *mystrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void undef(char *name)
{
    struct nlist *np, *fd;
    if ((np = lookup(name)) != NULL) {
        fd = hashtab[hash(name)];
        if (fd == np)
            hashtab[hash(name)] = np->next;
        else {
            for (;fd != NULL && fd->next != np; fd = fd->next)
                ;
            fd->next = np->next;
        }
        free((void *) np->defn);
        free((void *) np->name);
        free((void *) np);
    }
}