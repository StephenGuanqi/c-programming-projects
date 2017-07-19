#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define MAX_LINE 1000

ptrdiff_t my_getline(char *s, int max_length);

int main(int argc, char *argv[]) {
    char line[MAX_LINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {// if no more option, break the condition; the pattern is left
        while ((c = *++argv[0]))
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c.\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
    }
    if (argc != 1) {
        printf("Usage: find -x -n pattern \n");
    } else {
        while ( my_getline(line, MAX_LINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%ld ", lineno);
                }
                printf("%s", line);
                found++;
            }
        }
    }
    return found;
}