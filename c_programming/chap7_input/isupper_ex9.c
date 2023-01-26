#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0
#undef isupper

int isupper(int c)
{
    return (c >= 'A' && c <= 'Z');
}