#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXVAL 1000
#define NUMBER '0'

static int sp = 0;
static double val[MAXVAL];
void push(double f);
double pop(void);
int getop(char *s);

int main(int argc, char *argv[])
{
    int type;
    double op2;

    while (--argc > 0) {
        type = getop(*++argv);
        switch (type) {
        case NUMBER:
            push (atof(*argv));
            break;
        case '+':
            push (pop() + pop());
            break;
        case '*':
            push (pop() * pop());
            break;
        case '-':
            op2 = pop();
            push (pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push (pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        default:
            printf("error: unknown command %s\n", *argv);
            break;
        }
    }
    printf("\t%.8g\n", pop());
}

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char *s)
{
    if ((!isdigit(*s) && *s != '.' && *s != '-') || (*s == '-' && *(s+1) == '\0'))
        return *s;
    return NUMBER;
}