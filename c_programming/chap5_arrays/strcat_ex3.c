#include <stdio.h>
void strcat(char *s, char *t);

int main()
{
    char *s;
    char *t;
    scanf("%s", s);
    scanf("%s", t);
    strcat(s, t);
    printf("%s\n", s);
}

void strcat(char *s, char *t)
{
    while (*++s)
        ;
    while ((*s++ = *t++))
        ;
}