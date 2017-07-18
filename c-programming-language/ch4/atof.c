#include <ctype.h>
#include <stdio.h>
//stdlib.h has function of atof
// EOF, printf is declared in stdio.h

#define MAX_LINE 100

int main() {
    double sum, atof(char []);
    char line[MAX_LINE];
    // int getLine(char line[], int clang max);
    sum = 0;
    while (getLine(line, MAX_LINE) > 0) {
        printf("\t%g\n", sum += atof(line));
        test();
    }
    return 0;
}

double atof(char s[]) {
    int i, sign;
    double val, power;
    for (i = 0; isspace(i); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') 
        i++;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
    }
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        power *= 10.0;
        val = val * 10.0 + (s[i] - '0');
    }
    return sign * val / power;
}

// int getLine(char line[], int max_length) {
//     int c,i;
//     i = 0;
//     while (--max_length > 0 && (c = getchar()) != EOF && c != '\n')
//         line[i++] = c;
//     if (c == '\n')
//         line[i++] = c;
//     line[i] = 0;
//     return i;
// }