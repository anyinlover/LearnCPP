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
int _flushbuf(int, FILE *);

#define putc(x, p) (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuf((x), p))

int fflush(FILE *fp);
int fclose(FILE *fp);

int _flushbuf(int c, FILE *fp)
{
    int bufsize;
    int writesize;
    if ((fp->flag&(_WRITE | _ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    } else {
        writesize = write(fp->fd, fp->base, bufsize - fp->cnt);
        if (writesize != bufsize - fp->cnt) {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    *fp->ptr++ = c;
    fp->cnt = bufsize - 1;
    return 0;
}

int fflush(FILE *fp)
{
    _flushbuf(EOF, fp);
    fp->ptr--;
    fp->cnt++;
    return 0;
}

int fclose(FILE *fp)
{
    _flushbuf(EOF, fp);
    free(fp->base);
    close(fp->fd);
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


int fseek(FILE *fp, long offset, int origin);

int fseek(FILE *fp, long offset, int origin)
{
    if ((fp->flag & _READ) == _READ)
        lseek(fp->fd, -fp->cnt, 1);
    else if ((fp->flag & _WRITE) == _WRITE)
        fflush(fp);
    
    if (lseek(fp->fd, offset, origin) < 0)
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char buf;
    int i = 0;
    if((fp1 = fopen(argv[1], "r")) == NULL ||
        (fp2 = fopen(argv[2], "w")) == NULL)
        return 1;
    else
        while ((buf = getc(fp1)) != EOF && i++ < 5)
            putc(buf, fp2);
    fseek(fp1, 1, 1);
    fseek(fp2, 0, 0);
    while ((buf = getc(fp1)) != EOF && i++ < 10)
        putc(buf, fp2);

    fclose(fp1);
    fclose(fp2);
    return 0;
}