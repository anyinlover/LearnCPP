#include <stdio.h>
#include <stddef.h>
#define MAXLEN 1000
char *strncpy(char *s, char *ct, size_t n);
char *strncat(char *s, char *ct, size_t n);
int strncmp(char *cs, char *ct, size_t n);

int main()
{
    char s[MAXLEN] = "abcdfds";
    char t[MAXLEN] = "mng";
    size_t n = 3;
    printf("%s\n", strncpy(s, t, n));
    printf("%s\n", strncat(s, t, n));
    printf("%d\n", strncmp(s, t, n));
}

char *strncpy(char *s, char *ct, size_t n)
{
    size_t i = 0;
    while (*ct && i++ < n)
        *s++ = *ct++;

    while (i++ < n)
        *s++ = '\0';
    
    return s - n;
}

char *strncat(char *s, char *ct, size_t n)
{
    char *rs = s;
    size_t i = 0;
    while (*++s)
        ;
    
    while (i++ < n && (*s++ = *ct++))
        ;
    
    if (i < n)
        *s = '\0';
    
    return rs;
}

int strncmp(char *cs, char *ct, size_t n)
{
    size_t i = 0;
    while (i++ < n && (*cs++ == *ct++))
        if (*cs == '\0' || *ct == '\0' || i == n)
            return 0;
    
    return *cs - *ct;
}