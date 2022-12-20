#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000

void itoaw(int n, char s[], int w);
void reverse(char s[]);

int main()
{
    int n, w;
    char s[MAXLEN];
    scanf("%d", &n);
    scanf("%d", &w);
    itoaw(n, s, w);
    printf("%s\n", s);
}

void itoaw(int n, char s[], int w)
{
    int i, sign;
    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    while (i < w)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j, c;
    for (i = 0,j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
