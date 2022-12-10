#include <stdio.h>
#include <ctype.h>
#define MAXLEN 1000

void expand(char[] s1, char[] s2);

int main()
{
    char s1[MAXLEN];
    char s2[MAXLEN];
    expand(s1, s2);
    printf("%s\n", s2);
}

expand(char[] s1, char[] s2)
{
    int i, j;
    for (i = 1; (i < MAXLEN - 1) && (s1[i] != '\0'); i++) {
        if ((s1[i] == '-') && (
            (isdigit(s1[i-1]) && isdigit(s1[i+1])) ||
            (islower(s1[i-1]) && islower(s1[i+1])) ||
            (isupper(s1[i-1]) && isupper(s1[i+1]))
            ) && (s1[i+1] > s1[i-1])) {
            for (s2[j] = s1[i-1] + 1; s[j])
        }
    }
}