#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 1000

double atof(char s[]);

int main()
{
    char s[MAXLEN];
    scanf("%s", &s);
    printf("%f\n", atof(s));
}

double atof(char s[])
{
    double val, power, exp_val;
    int i, sign, exp_sign;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    exp_val = 1;
    if (s[i] == 'e') {
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;
        for (exp_val = 0.0; isdigit(s[i]); i++)
            exp_val = 10.0 * exp_val + (s[i] - '0');
            exp_val = pow(10.0, exp_val);
            if (exp_sign < 0)
                exp_val = 1 / exp_val;
    }
    
    return sign * val * exp_val / power;
}