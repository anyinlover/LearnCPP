#include <stdio.h>
#include <string.h>
#define MAXLEN 1000
int strend(char *s, char *t);

int main()
{
    char s[MAXLEN];
    char t[MAXLEN];
    scanf("%s", &s);
    scanf("%s", &t);
    printf("%d\n", strend(s, t));
}

int strend(char *s, char *t)
{
    int sl, tl;
    sl = strlen(s);
    tl = strlen(t);
    while (sl >= 0 && tl >= 0 && *(s+sl) == *(t+tl)) {
        sl--;
        tl--;
    }
    return tl == -1 ? 1 : 0; 
}
