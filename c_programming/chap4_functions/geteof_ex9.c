#include <stdio.h>
#define BUFSIZE 100
int bufp;
char buf[BUFSIZE];

int getch(void);
void ungetch(int c);

int main()
{
    ungetch('a');
    ungetch(EOF);
    printf("%c\n",getch());
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (c == EOF)
        return;
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}