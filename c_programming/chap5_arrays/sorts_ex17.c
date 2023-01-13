#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 1000
#define MAXLINES 1000
#define FIELDNUM 3

char *lineptr[MAXLINES];


int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void myqsort(void *lineptr[], int left, int right, int (*comp) (void *, void *, void *, void *));
int mygetline(char *s, int lim);
void swap(void *v[], int i, int j);
int numcmpr(char *s1, char *s2);
int strcmpr(char *s1, char *s2);
int linecmp(char *s1, char *s2, char *s1f, char *s2f);

int reverses[FIELDNUM];
int folds[FIELDNUM];
int directories[FIELDNUM];
int numerics[FIELDNUM];
int i;

int main(int argc, char *argv[])
{
    int nlines, c, i;
    
    for (i = 0; --argc > 0 && (*++argv)[0] == '-'; i++) {
        while ((c = *++argv[0]))
            switch (c) {
            case 'n':
                numerics[i] = 1;
                break;
            case 'r':
                reverses[i] = 1;
                break;
            case 'f':
                folds[i] = 1;
                break;
            case 'd':
                directories[i] = 1;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                break;
            }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort(lineptr, 0, nlines - 1,
            (int (*)(void *, void *, void *, void *))(linecmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int mygetline(char *s, int lim)
{
    int c;
    char *sb;
    c = 0;
    sb = s;
    for (; (c = getchar()) != EOF && c != '\n';*s++ = c)
        ;

    if (c == '\n') {
        *s++ = c;
    }

    *s = '\0';

    return s - sb;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = (char*) malloc(len * sizeof(char))) == NULL)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void myqsort(void *v[], int left, int right,
            int (*comp)(void *, void *, void *, void *))
{
    static char s1field[MAXLEN];
    static char s2field[MAXLEN];
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left], s1field, s2field) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmpr(char *s1, char *s2)
{
    int r;
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        r = -1;
    else if (v1 > v2)
        r = 1;
    else
        r = 0;
    return reverses[i] ? -r : r;
}

int strcmpr(char *s1, char *s2)
{
    char c1, c2;
    int r;
    c1 = 0;
    c2 = 0;
    while (c1 == c2) {
        c1 = *s1++;
        c2 = *s2++;
        if (directories[i]) {
            while (c1 != '\0' && !isalnum(c1) && !isblank(c1))
                c1 = *s1++;
            while (c2 != '\0' && !isalnum(c2) && !isblank(c2))
                c2 = *s2++;
        }
        if (folds[i]) {
            if isupper(c1)
                c1 += 'a' - 'A';
            if isupper(c2)
                c2 += 'a' - 'A';
        }
    }
    if (c1 == '\0')
        r = 0;
    else
        r = c1 - c2;
    return reverses[i] ? -r : r;
}

int linecmp(char *s1, char *s2, char *s1field, char *s2field)
{
    int r;
    char *s1b, *s2b;
    for (i = 0; i < FIELDNUM; i++) {
        s1b = s1field;
        s2b = s2field;
        for (*s1field = *s1++; *s1field != '\t' && *s1field != '\0'; s1field++)
            *s1field = *s1++;
        *s1field++ = '\0';
        for (*s2field = *s2++; *s2field != '\t' && *s2field != '\0'; s2field++)
            *s2field = *s2++;
        *s2field++ = '\0';
        r = numerics[i] ? numcmpr(s1b, s2b) : strcmpr(s1b, s2b);
        if (r != 0)
            return r;
    }
    return 0;
}


