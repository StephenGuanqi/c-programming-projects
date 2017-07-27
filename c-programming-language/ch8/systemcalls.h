#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag; // mode
    int fd;
}FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ  = 01,
    _WRITE = 02,
    _UNBUF = 04,  /* no buffer for the file */
    _EOF   = 010, /* end of file*/
    _ERR   = 020  /* the error occured in this file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)   (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    {0, (char *)0, (char *)0, _READ, 0},
    {0, (char *)0, (char *)0, _WRITE, 1},
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2} // define UNBUF to continuously invoke fillbuf or flushbuf
};

#endif

