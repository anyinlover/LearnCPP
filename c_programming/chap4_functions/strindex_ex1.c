#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

int strindex(char s[], char t[]);
int mygetline(char s[], int lim);

int main()
{
    char s[MAXLEN];
    char t[MAXLEN];
    mygetline(s, MAXLEN);
    mygetline(t, MAXLEN);
    printf("%d\n", strindex(s, t));
}

int mygetline(char s[], int lim)
{
    int i, c;
    i = c = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';

    return i;
}
int strindex(char s[], char t[])
{
    int sl = strlen(s);
    int tl = strlen(t);
    int i, j, k;
    for (i = sl - tl; i >= 0; i--) {
        for (j = i, k = 0; t[k] != 0 && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}