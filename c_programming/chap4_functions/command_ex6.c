#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define VARMAX 27

int sp = 0;
double val[MAXVAL];
double vars[VARMAX];
char buf[BUFSIZE];
int bufp = 0;
double last;

void push(double f);
double pop(void);
int getch(void);
void ungetch(int);
int getop(char s[]);

int main()
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push (atof(s));
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
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push (fmod(pop(),op2));
            else
                printf("error: zero modulor\n");
            break;
        case 's':
            push(sin(pop()));
            break;
        case 'e':
            push(exp(pop()));
            break;
        case 'p':
            op2 = pop();
            op1 = pop();
            if ((op1 == 0.0 && op2 <=0) || op1 < 0)
                printf("error: x or y is not right.");
            else
                push(pow(op1, op2));
            break;

        case '\n':
            last = pop();
            printf("\t%.8g\n", last);
            break;
        default:
            if (type >= 'A' && type <= 'Z')

                if (strlen(s) > 0)
                    vars[type-'A'] = atof(s);
                else
                    push(vars[type-'A']);
            else
                printf("error: unknown command %s\n", s);
            break;
        }
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

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getop(char s[])
{
    int i, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (c >= 'A' && c <= 'Z') {
        i = -1 ;
        while (i < 0 || (s[i] != ' ' && s[i] != '\n'))
            s[++i] = getch();
        s[i] = '\0';
        return c;
    }
    if (!isdigit(c) && c != '.' && c != '-' )
        return c;
    if (c == '-') {
        next = getch();
        if (next == ' ')
            return c;
        else
            ungetch(next);
    }
    i = 0;
    if (isdigit(c) || c == '-')
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
