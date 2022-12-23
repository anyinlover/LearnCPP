#include <stdio.h>
#define MAXLEN 1000

void itoa(int n, char s[]);

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
    static int i = 0;
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    s[i++] = n % 10 + '0';
}
