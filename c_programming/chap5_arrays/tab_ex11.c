#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000

int mygetline(char s[], int lim);
void detab(char *s, char *ns, int *tabstops);
void entab(char *s, char *ns, int *tabstops);

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
    char s[MAXLEN], ns[MAXLEN];
    int tabstops[argc - 1];
    int i = 0;
    while (--argc > 0)
        tabstops[i++] = atoi(*++argv);
    tabstops[i] = -1;
    mygetline(s, MAXLEN);
    detab(s, ns, tabstops);
    printf("%s", ns);
    entab(ns, s, tabstops);
    printf("%s", s);
}

void detab(char *s, char *ns, int *tabstops)
{
    int i;
    i = 0;
    while (*s != '\0') {
        if (i == *tabstops)
            tabstops++;
        if (*s == '\t') {
            while (i < *tabstops) {
                ns[i++] = ' ';
            }
        } else {
            ns[i++] = *s;
        }
        s++;
    }
    ns[i] = '\0';
}

void entab(char *s, char *ns, int *tabstops)
{
    int i, j;
    i = 0;
    j = 0;
    while (s[i] != '\0') {
        if (i == *tabstops)
            tabstops++;
        if (s[i] != ' ') {
            while (j > 0) {
                *ns++ = ' ';
                j--;
            }
            *ns++ = s[i];
        } else {
            j++;
            if (i == *tabstops) {
                *ns++ = '\t';
                j = 0;
            }
        }
        i++;
    }
    *ns = '\0';
}
