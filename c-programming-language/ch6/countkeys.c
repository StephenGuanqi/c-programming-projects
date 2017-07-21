#include <stdio.h>
#include <string.h>
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0}
};

int binarysearch(char *, struct key *, int);
struct key *binarysearch2(char *, struct key *, int);

int binarysearch(char *word, struct key tab[], int n) {
    int cond, mid;
    int low = 0;
    int high = n-1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (( cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

struct key *
binarysearch2(char *word, struct key *tab, int n) {
    struct key * low = tab;
    struct key * high = tab + n;
    struct key * mid;
    int cond;
    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid -> word)) < 0) {
            high = mid;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return NULL;
}