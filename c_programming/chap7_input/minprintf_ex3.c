#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);


int main()
{
    minprintf("hello %s %d %e %% %X", "hello", 89, 90.42, 90);
    return 0;
}
void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, format[3] = {'%', '\0', '\0'};
    int ival;
    double dval;
    unsigned uval;
    void *pval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
        case 'c':
            ival = va_arg(ap, int);
            format[1] = *p;
            printf(format, ival);
            break;
        case 'x':
        case 'X':
        case 'o':
        case 'u':
            uval = va_arg(ap, unsigned int);
            format[1] = *p;
            printf(format, uval);
            break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            dval = va_arg(ap, double);
            format[1] = *p;
            printf(format, dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        case '%':
            putchar(*p);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}