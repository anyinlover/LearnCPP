#include <stdio.h>
#include <stdarg.h>
#define MAXLEN 100

void minscanf(char *fmt, ...);

int main()
{
    char str[MAXLEN];
    int i;
    float d; 
    unsigned u;
    minscanf("%s %i %u %f", str, &i, &u, &d);
    printf("%s %i %u %f\n", str, i, u, d);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sptr, format[3] = {'%', '\0', '\0'};
    int *iptr;
    unsigned *uptr;
    float *fptr;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
        case 'c':
            iptr = va_arg(ap, int*);
            format[1] = *p;
            scanf(format, iptr);
            break;
        case 'x':
        case 'o':
        case 'u':
            uptr = va_arg(ap, unsigned *);
            format[1] = *p;
            scanf(format, uptr);
            break;
        case 'e':
        case 'f':
        case 'g':
            fptr = va_arg(ap, float *);
            format[1] = *p;
            scanf(format, fptr);
            break;

        case 's':
            sptr = va_arg(ap, char *);
            scanf("%s", sptr);
            break;
        case '%':
            scanf("%%");
            break;
        default:
            break;
        }
    }
    va_end(ap);
}