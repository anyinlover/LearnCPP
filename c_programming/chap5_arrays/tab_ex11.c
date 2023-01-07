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
        if (*s == '\t') {
            while (i < *tabstops) {
                ns[i++] = ' ';
            }
            tabstops++;
        } else {
            ns[i++] = *s;
            if (i == *tabstops)
                tabstops++;
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
        if (s[i] != ' ') {
            while (j > 0) {
                *ns++ = ' ';
                j--;
            }
            *ns++ = s[i];
            if (i == *tabstops)
                tabstops++;
        } else {
            j++;
            if (i == *tabstops) {
                *ns++ = '\t';
                j = 0;
                tabstops++;
            }
        }
        i++;
    }
    *ns = '\0';
}
