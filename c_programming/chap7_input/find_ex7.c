#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int main(int argc, char *argv[])
{
    char line[MAXLINE], *pattern;
    long lineno = 0;
    FILE *fp;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                return -1;
            }
    
    pattern = *argv;
    if (--argc > 0) {
        while (argc-- > 0) {
            fp = fopen(*++argv, "r");
            if (fp == NULL) {
                fprintf(stderr, "%s file is not correct\n", *argv);
                return -1;
            }
            lineno = 0;
            while (fgets(line, MAXLINE, fp)) {
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    printf("%s: ", *argv);
                    if (number)
                        printf("%ld: ", lineno);
                    printf("%s", line);
                    found++;
                }
            }
            fclose(fp);
        }
    } else {
        while (fgets(line, MAXLINE, stdin)) {
            lineno++;
            if ((strstr(line, pattern) != NULL) != except) {
                if (number)
                    printf("%ld: ", lineno);
                printf("%s", line);
                found++;
            }
        }
    }
    return found;
}