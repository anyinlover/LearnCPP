#include <stdio.h>
#define MAXLEN 1000

void convert(char s[], char t[]);
void convert2(char y[], char s[]);
int mygetline(char s[], const int lim);

int main()
{
    char t[MAXLEN];
    char s[MAXLEN];
    char y[MAXLEN];
    mygetline(t, MAXLEN);
    printf("%s\n", t);
    convert(s, t);
    printf("%s\n", s);
    convert2(y, s);
    printf("%s\n", y);
}

void convert(char s[], char t[])
{
    int i, j;
    i = j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
        i++;
    }
    s[j] = '\0';
}

void convert2(char y[], char s[])
{
    int i, j;
    i = j = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
        case '\\':
            switch (s[i+1]) {
            case 't':
                y[j++] = '\t';
                i += 2;
                break;
            case 'n':
                y[j++] = '\n';
                i += 2;
                break;
            default:
                break;
            }
            break;
        default:
            y[j++] = s[i++];
            break;
        }
    }
    y[j] = '\0';
}

int mygetline(char s[], const int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}