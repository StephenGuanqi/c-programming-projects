#include <stdio.h>
#include <string.h>
#define  MAX_LINE 1000

char *lineptr[MAX_LINE];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int reverse);

int numcmp(char *, char *);
typedef int (*PFI)(char *, char *);
PFI numcmp2, strcmp2;

int main(int argc, char *argv[]) {
    int c;
    int numeric = 0, reverse = -1;// -1 for do not reverse sort
    int nlines; // number of lines to read in
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                default: 
                    argc = 1;
            }
        }
    }
    if (argc != 0) {
        printf("Usage: sort -n -r \n");
    }else {
        if ((nlines = readlines(lineptr, MAX_LINE)) >= 0 ) {
            qsort((void **)lineptr, 0, nlines-1, (int (*)(void *, void*)) (numeric? numcmp : strcmp), reverse);
            writelines(lineptr, nlines);
            return 0;
        } else {
            printf("input too big to sort. \n");
            return 1;
        }
    }
}

#define MAX_LENG 100
char* alloc(int n);
int getLine(char line[], int max_length);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char line[MAX_LENG], *p;
    nlines = 0;
    while ((len = getLine(line, MAX_LENG)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len-1] = '\0';
        // p = line;// wrong wrong wrong
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void qsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse) {
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) 
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) * -1 * reverse < 0 )
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1, comp, reverse);
    qsort(v, last+1, right, comp, reverse);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char*s2) {
    double atof(char *s);
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

