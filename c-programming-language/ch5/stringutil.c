#include <stddef.h>
#include <string.h>
#include <stdio.h>

int mstrlen(char *s) {
    int n;
    for (n = 0; *s != 0; s++) {
        n++;
    }
    return n;
}

ptrdiff_t mystrlen(char *s) {
    char *p = s;
    while (*p != '\0') {
        p++;
    }
    return p-s;
}

void mystrcpy(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

int mystrcmp(char *s, char *t) {
    for (; *s == *t; s++, t++) {
        if (*s == 0)
            return 0;
    }
    return *s - *t;
}

void mystrcat(char *s, char *t) {
    size_t length = strlen(s);
    s += length;
    while (*s++ = *t++)
        ;
}

void reverse(char *s) {
    int length = mystrlen(s);
    char *end = s + length - 1;
    while ( s < end) {
        char tmp = *end;
        *end = *s;
        *s = tmp;
        s++;
        end--;
    }
}

int main() {

    char *s = "string";
    printf("%ld\n", strlen(s));
    printf("%d\n", mystrlen(s));
}