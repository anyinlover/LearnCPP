#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

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

double top(void)
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void dup(void)
{
    if (sp > 0)
        push(top());
    else
        printf("error: stack empty\n");
}

void swap(void)
{
    if (sp > 1) {
        double v1, v2;
        v1 = pop();
        v2 = pop();
        push(v1);
        push(v2);
    } else {
        printf("error: not enough elements\n");
    }
}

void clear(void)
{
    while (sp)
        pop();
}