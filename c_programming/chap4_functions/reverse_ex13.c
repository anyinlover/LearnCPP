#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

void reverse(char s[]);

int main()
{
    char s[MAXLEN];
    scanf("%s", &s);
    reverse(s);
    printf("%s\n", s);
}

void reverse(char s[])
{
    static int i = 0, n;

    if (s[i]) {
        int c = s[i++];
        reverse(s);
        s[n-i] = c;
        i--;
    } else {
        n = i;
    }
}
