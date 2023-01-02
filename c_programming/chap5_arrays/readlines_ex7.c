#include <stdio.h>
#include <string.h>
#define MAXLEN 1000
#define MAXLINES 1000
#define MAXSTORES MAXLEN * MAXLINES

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char *stores, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int mygetline(char *s, int lim);
void swap(char *v[], int i, int j);

int main()
{
    int nlines;
    char stores[MAXSTORES];
    if ((nlines = readlines(lineptr, stores, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
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

int readlines(char *lineptr[], char *stores, int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    p = stores;
    
    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p - stores >= MAXSTORES)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right)
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

