#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000
#define MAXLINES 1000
#define TAILLEN 10

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int ntail);
int mygetline(char *s, int lim);

int main(int argc, char *argv[])
{
    int nlines, n, c;
    n = TAILLEN;
    if (argc > 1) {
        c = (*++argv)[0];
        if (c == '-') 
            n = atoi(++argv[0]);
    }
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (nlines < n)
            n = nlines;
        writelines(lineptr, nlines, n);
        return 0;
    } else {
        printf("error: input too big to tail\n");
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

void writelines(char *lineptr[], int nlines, int ntail)
{
    while (nlines > ntail) {
        lineptr++;
        nlines--;
    }
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}


