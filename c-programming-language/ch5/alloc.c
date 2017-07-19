#include <string.h>
#include <stdio.h>
#define ALLOCSIZE 30

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;



char* alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n ) {
        allocp += n;
        return allocp - n;
    } else {
        printf("no enough space to allocate.");
        return 0;
    }
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

