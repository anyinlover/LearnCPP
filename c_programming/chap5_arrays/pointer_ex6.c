#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXLEN 1000
int mygetline(char *s, int lim);
int atoi(char *s);
void itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);

int main()
{
    char s[MAXLEN];
    char t[MAXLEN];
    int n;
    mygetline(s, MAXLEN);
    printf("%s\n", s);
    n = atoi(s);
    printf("%d\n", n);
    itoa(n, s);
    printf("%s\n", s);
    scanf("%s", &t);
    printf("%d\n", strindex(s, t));
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

int atoi(char *s)
{
    int n = 0;
    while (*s >= '0' && *s <= '9')
        n = 10 * n + (*s++ - '0');

    return n;
}

void itoa(int n, char *s)
{

    int sign;
    sign = n;
    char *rs = s;
    do {
        *s++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(rs);
}

void reverse(char *s)
{
    int i, j, c;
    for (i = 0,j = strlen(s) - 1; i < j; i++, j--) {
        c = *(s + i);
        *(s + i) = *(s + j);
        *(s + j) = c;
    }
}

int strindex(char *s, char *t)
{
    char *rs = s;
    char *sc, *tc;
    while (*s != '\0') {
        for (sc = s, tc = t; *tc != '\0' && *sc == *tc; sc++, tc++)
            ;
        if (tc > t && *tc == '\0')
            return s - rs;
        s++;
    }
    return -1;
}