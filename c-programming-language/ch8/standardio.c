// #include "syscalls.h"
#include <stdio.h>
#include <unistd.h>
#undef getchar

int main(){
    char buf[BUFSIZ];
    int n;
    while ((n = read(0, buf, BUFSIZ)) > 0)// 0 for end of file, -1 for error occurred, others for actual number of bytes
        write(1, buf, n);
    return 0;
}

// no buffer
int getchar(void) {
    char c;
    return (read(0, &c, 1)) == 1 ? (unsigned char) c : EOF;
}

// buffer
int getchar2(void) {
    static char buf[BUFSIZ];// buf shouold remain the same for the memory allocation
    static char *bufp = buf;
    static int n = 0;
    if ( n == 0) {
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}