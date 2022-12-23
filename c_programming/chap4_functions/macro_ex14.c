#include <stdio.h>
#define swap(t, x, y) t tmp; tmp = x; x = y; y = tmp;

int main()
{
    int x = 3;
    int y = 5;
    swap(int, x, y);
    printf("%d %d\n", x, y);
}