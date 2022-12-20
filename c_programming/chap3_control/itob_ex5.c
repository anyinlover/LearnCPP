#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    int n, b;
    char s[MAXLEN];
    scanf("%d", &n);
    scanf("%d", &b);
    itob(n, s, b);
    printf("%s\n", s);
}

void itob(int n, char s[], int b)
{
    int i, k, sign;
    sign = n;
    i = 0;
    do {
        k = abs(n % b);
        s[i++] = k < 10 ? k + '0' : k - 10 + 'A';
    } while ((n /= b) != 0);
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
