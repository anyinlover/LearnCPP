#include <stdio.h>
#define MAXLINE 1000
#define MAXLEN 10

int main(int argc, char *argv[])
{
    long lineno;
    FILE *fp;
    char line[MAXLINE];
    while (--argc > 0) {
        if((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s is not a correct file", *argv);
            return -1;
        }
        lineno = 0;
        while (fgets(line, MAXLINE, fp)) {
            if (lineno % 10 == 0) {
                printf("\n%s: line %ld\n", *argv, lineno+1);
            }
            lineno++;
            printf("%s", line);
        }
        fclose(fp);
    }
    return 0;
}