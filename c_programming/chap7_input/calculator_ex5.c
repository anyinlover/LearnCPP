#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'

int sp = 0;
double val[MAXVAL];

void push(double f);
double pop(void);
int getop(char s[]);

int main()
{
    int type;
    float op2;
    char s[MAXOP], c;

    while (scanf("%s%c", s, &c) == 2) {
        if (sscanf(s, "%f", &op2) == 1) {
            push(op2);
        }
        else {
            switch (*s) {
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
                printf("error: unknown command %s\n", s);
                break;
            }
        }
        if (c == '\n')
            printf("\t%.8g\n", pop());
    }
    return 0;
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

int getop(char s[])
{
    scanf("%s", s);
    if (isdigit(s[0]) || s[0] == '.' || (s[0] == '_' && s[1] != '\0'))
        return NUMBER;
    else
        return s[0];
}
