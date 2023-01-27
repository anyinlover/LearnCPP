#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define PERMS 0666
#define BUFSIZ 8196
#define OPEN_MAX 20
#define EOF -1

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

enum _flags {
    _READ   = 01,
    _WRITE  = 02,
    _UNBUF  = 04,
    _EOF    = 010,
    _ERR    = 020
};

FILE _iob[OPEN_MAX] = {
    {0, (char *) 0, (char *) 0, _READ, 0 },
    {0, (char *) 0, (char *) 0, _WRITE, 1 },
    {0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int _fillbuf(FILE *fp);
#define getc(p)     (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

FILE *fopen(char *name, char *mode);

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[1];

    while (--argc > 0)
        if ((fp = fopen(*++argv, "r")) == NULL)
            return 1;
        else
            while ((buf[0] = getc(fp)) != EOF)
                write(1, buf, 1);
    return 0;
}

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag % 2 == 0 && fp->flag >> 1 % 2 == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;
    
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;
    if (fp->flag % 2 == 0 || (fp->flag >> 3) % 2 == 1 || (fp->flag >> 4) % 2 == 1)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            if ((fp->flag >> 3) % 2 == 0)
                fp->flag += _EOF;
        else
            if ((fp->flag >> 4) % 2 == 0)
                fp->flag += _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}