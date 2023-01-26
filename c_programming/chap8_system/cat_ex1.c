#include "unistd.h"

void filecopy(int f1, int f2);

int main(int argc, char *argv[])
{
    int f;
    if (argc == 1) {
        filecopy(0, 1);
    } else {
        while (--argc > 0)
            if ((f = open(*++argv, O_RDONLY, 0)) == -1) {
                error("cat: can't open %s", *argv);
                exit(1);
            } else {
                filecopy(f, 1);
                close(f);
            }
    }
    exit(0);
}

void filecopy(int f1, int f2)
{
    char buf[BUFSIZ];
    int n;
    while ((n = read(f1, buf, BUFSIZ)) > 0)
        if (write(f2, buf, n) != n) {
            error("cp: write error");
            exit(2);
        }
}