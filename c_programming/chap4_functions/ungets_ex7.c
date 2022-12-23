#include <stdio.h>
#include <string.h>
#define BUFSIZE 100
int bufp;
char buf[BUFSIZE];

int getch(void);
void ungetch(int c);
void ungets(char s[]);

int main()
{
    ungets("abc");
    printf("%c\n",getch());
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])
{
    int i, len;
    len = strlen(s);
    if (BUFSIZE - bufp >= len)
    {
        for (i = len - 1; i >= 0; i--)
            ungetch(s[i]);
    } else {
        printf("error: buffer space is not enough.");
    }
}