#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;
    char *s;
    int useOct = 0;
    if (argc > 1 && strcmp(*++argv, "-o") == 0) {
        useOct = 1;
    }
    while ((c = getchar()) != EOF) {
        if (isgraph(c) || isspace(c)) {
            putchar(c);
        } else {
            printf(useOct ? "%o" : "%x", c);
        }
    }
    return 0;
}