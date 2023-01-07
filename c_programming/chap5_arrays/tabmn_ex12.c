#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000
#define N 8

int mygetline(char s[], int lim);
void detab(char *s, char *ns, int m, int n);
void entab(char *s, char *ns, int m, int n);

int mygetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

int main(int argc, char *argv[])
{
    int m, n, c;
    m = 0;
    n = N;
    while (--argc > 0) {
        c = (*++argv)[0];
        switch (c) {
            case '-':
                m = atoi(++argv[0]);
                break;
            case '+':
                n = atoi(++argv[0]);
                break;
            default:
                printf("tab: illegal option %c\n", c);
                break;          
        }
    }
    char s[MAXLEN], ns[MAXLEN];
    mygetline(s, MAXLEN);
    detab(s, ns, m, n);
    printf("%s", ns);
    entab(ns, s, m, n);
    printf("%s", s);
}

void detab(char *s, char *ns, int m, int n)
{
    int i;
    i = 0;
    while (*s != '\0') {
        if (i == m)
            m += n;
        if (*s == '\t') {
            while (i < m) {
                ns[i++] = ' ';
            }
        } else {
            ns[i++] = *s;
        }
        s++;
    }
    ns[i] = '\0';
}

void entab(char *s, char *ns, int m, int n)
{
    int i, j;
    i = 0;
    j = 0;
    while (s[i] != '\0') {
        if (i == m)
            m += n;
        if (s[i] != ' ') {
            while (j > 0) {
                *ns++ = ' ';
                j--;
            }
            *ns++ = s[i];
        } else {
            j++;
            if (i == m) {
                *ns++ = '\t';
                j = 0;
            }
        }
        i++;
    }
    *ns = '\0';
}

