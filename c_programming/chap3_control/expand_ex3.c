#include <stdio.h>
#include <ctype.h>
#define MAXLEN 1000

void expand(char s1[], char s2[]);
int mygetline(char s[], const int lim);

int main()
{
    char s1[MAXLEN];
    char s2[MAXLEN];
    mygetline(s1, MAXLEN);
    expand(s1, s2);
    printf("%s\n", s2);
}

void expand(char s1[], char s2[])
{
    s2[0] = s1[0];
    if (s1[0] == '\0') {
        return;
    }
    int i, j, k;
    for (i = 1, j = 1; (i < MAXLEN - 1) && (j < MAXLEN - 1) && (s1[i] != '\0'); i++) {
        if ((s1[i] == '-') && (
            (isdigit(s1[i-1]) && isdigit(s1[i+1])) ||
            (islower(s1[i-1]) && islower(s1[i+1])) ||
            (isupper(s1[i-1]) && isupper(s1[i+1]))
            ) && (s1[i+1] > s1[i-1])) {
            for (k = 1; (k < s1[i+1] - s1[i-1]) && (j < MAXLEN - 1); k++,j++) {
                s2[j] = s1[i-1] + k;
            } 
        } else {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}

int mygetline(char s[], const int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    s[i] = '\0';
    return i;
}