#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    int n;
    char s[MAXLEN];
    scanf("%d", &n);
    itoa(n, s);
    printf("%s\n", s);
}

void itoa(int n, char s[])
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