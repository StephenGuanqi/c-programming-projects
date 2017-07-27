#include "systemcalls.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define PERMS 0666

FILE *fopen(char *filename, char *mode) {
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break; /* search for the next empty location */
    if (fp >= _iob + OPEN_MAX)  
        return NULL;
    if (*mode == 'w')
        fd = creat(filename, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(filename, O_WRONLY, 0)) == -1 )
            fd = creat(filename, PERMS);
        lseek(fd, 0L, 2);
    } else 
        fd = open(filename, O_RDONLY, 0);
    if (fd == -1) /* the name is unable to access */
        return NULL;
    fp->cnt = 0;
    fp->fd = fd;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp; // check validity out sied of the function
}

int _fillbuf(FILE *fp) {
    int bufsize;
    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) // mode include READ but not include EOF or ERR
    // fp->flag & _READ == _READ for contains _READ
    // fp->flag & _READ == 0 for not contains _READ
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
    if (fp->base == NULL) 
        if ((fp->base = (char *)malloc(bufsize)) == NULL) // only init at the first time
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->base, BUFSIZE); // read return 0 for end of file; -1 for error
    if (--fp->cnt < 0) {// reduce cnt by one to return one character for this function
        if (fp->cnt == -1) // the input file has come to end
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp) {
    int num_written, bufsize;
    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;
    if (fp->base == NULL && ((fp->flag & _UNBUF) == 0)) {
        /* no buffer yet*/
        if ((fp->base = (char *)malloc(BUFSIZE)) == NULL)
            return EOF;
        else {
            fp->cnt = BUFSIZE-1;
            fp->ptr = fp->base;
        }
    }
        
    if (fp->flag & _UNBUF) {
        fp->ptr = fp->base = NULL;
        fp->cnt = 0;
        if (c == EOF)
            return EOF;
        num_written = write(fp->fd, &c, 1);
        bufsize = 1;
    } else {
        if (c != EOF) // reject EOF as input; make EOF as flush symbol
            *fp->ptr++ = c;
        bufsize = (int)(fp->ptr - fp->base);
        num_written = write(fp->fd, fp->base, bufsize);
        fp->ptr = fp->base;// two pointer always euqals after this method invocation
        fp->cnt = BUFSIZE - 1;
    }
    if (num_written == bufsize)
        return c;
    else 
        fp->flag |= _ERR;
        return EOF;
}

int fflush(FILE *fp){
    FILE *fpt;
    int all_finished = 0;
    if (fp == NULL) {
        /* will be called when the exit is called or main is returned */
        for (fpt = _iob; fpt < _iob + OPEN_MAX; fpt++)
            if ((fpt->flag & _WRITE) && (fflush(fpt) == -1))
                all_finished = -1;
    } else {
        if ((fp->flag & _WRITE) == 0)
            return -1;
        _flushbuf(EOF, fp); // flush the buffer chars in the base
        if (fp->flag & _ERR) // error occured during the flush function
            all_finished = -1; 
    }
    return all_finished;
}

int fclose(FILE *fp) {
    int fd;
    if (fp == NULL)
        return -1;
    fd = fp->fd;
    fflush(fp);
    fp->cnt = 0;
    fp->ptr = NULL;
    // free(fp->base);// same as malloc, always check
    if (fp->base != NULL)
        free(fp->base);
    fp->base = NULL;
    fp->flag = 0;
    fp->fd = -1;
    return close(fd);
}