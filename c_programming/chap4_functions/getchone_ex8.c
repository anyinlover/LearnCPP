#include <stdio.h>
#define BUFSIZE 100
int bufc = -1;

int getch(void);
void ungetch(int c);

int main()
{
    ungetch('a');
    printf("%c\n",getch());
}

int getch(void)
{
    int tmp;
    if (bufc >= 0) {
        tmp = bufc;
        bufc = -1;
        return tmp;
    } else
        return getchar();
}

void ungetch(int c)
{
    bufc = c;
}
