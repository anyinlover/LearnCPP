#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char ln1[MAXLEN], ln2[MAXLEN];
    if (argc != 3) {
        fprintf(stderr, "%s don't have right parameters", *argv);
        exit(1);
    }
    if ((fp1 = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s is not a corrent file", *argv);
        exit(2);
    }
    if ((fp2 = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s is not a corrent file", *argv);
        exit(2);
    }
    while (fgets(ln1, MAXLEN, fp1) && fgets(ln2, MAXLEN, fp2)) {
        if (strcmp(ln1, ln2)) {
            printf("%s%s", ln1, ln2);
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
    exit(0);
}