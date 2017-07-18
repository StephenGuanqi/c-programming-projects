#include <stdio.h>
#define MAX_LINE 1000

int getLine(char line[], int max_length);
int stringIndex(char source[], char searchfor[]);

char pattern[] = "ould";

int main() {
    char line[MAX_LINE];
    int found = 0;
    while(getLine(line, MAX_LINE) > 0) {
        if (stringIndex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    }
    return found;
}

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

int stringIndex(char source[], char searchfor[]) {
    int i, j, k;
    for (i = 0; source[i]; i++) {
        for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
            ;
        if (k > 0 && searchfor[k] == '\0') // k > 0 to prevent the searchFor is null cstring but return 0 for the function
            return i;
    }
    return -1;
}