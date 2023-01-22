#include <stdio.h>
#include <ctype.h>
#include <string.h>

int lastequal(char *s, char *t);

int main(int argc, char *argv[])
{
    int c;
    if (lastequal(argv[0], "lower") == 0) {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    } else {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    }
    return 0;
}

int lastequal(char *s, char *t)
{
    char *lastOne;
    lastOne = strrchr(s, '/');
    if (lastOne) {
        return strcmp(lastOne + 1, t);
    }
    return strcmp(s, t);
}