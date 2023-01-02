#include <stdio.h>
#define MAXLEN 1000
void strcat(char *s, char *t);

int main()
{
    char s[MAXLEN];
    char t[MAXLEN];
    scanf("%s", &s);
    scanf("%s", &t);
    strcat(s, t);
    printf("%s\n", s);
}

void strcat(char *s, char *t)
{
    while (*++s)
        ;
    while ((*s++ = *t++)) {
        ;
    }
}