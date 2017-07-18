#include <stdio.h>

int getLine(char line[], int max_length);
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

void test() {
    printf("test succeed.\n");
}