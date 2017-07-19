#include <stdio.h>
#include <stddef.h>

int getLine(char line[], int max_length);
ptrdiff_t my_getline(char line[], int max_length);
static void test();

int getLine(char line[], int max_length) {
    int c,i;
    i = 0;
    while (--max_length > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = 0;
    return i;
}

ptrdiff_t my_getline(char *s, int max_length) {
    int c,i;
    char *start = s;
    while (--max_length > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = 0;
    return s-start;
}

void test() {
    printf("test succeed.\n");
}
