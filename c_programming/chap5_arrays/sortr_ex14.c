#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000
#define MAXLINES 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int reverse, int (*comp) (void *, void *, int));
int mygetline(char *s, int lim);
void swap(void *v[], int i, int j);
int numcmpr(char *s1, char *s2, int reverse);
int strcmpr(char *s1, char *s2, int reverse);

int main(int argc, char *argv[])
{
    int nlines, reverse, numeric, c;
    reverse = 0;
    numeric = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                break;
            }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1, reverse,
            (int (*)(void *, void *, int))(numeric ? numcmpr : strcmpr));
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

void qsort(void *v[], int left, int right, int reverse,
            int (*comp)(void *, void *, int))
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left], reverse) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1, reverse, comp);
    qsort(v, last+1, right, reverse, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmpr(char *s1, char *s2, int reverse)
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
    return reverse ? -r : r;
}

int strcmpr(char *s1, char *s2, int reverse)
{
    int r = strcmp(s1, s2);
    return reverse ? -r : r;
}

