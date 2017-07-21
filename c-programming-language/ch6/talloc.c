#include <stdlib.h>
#include <string.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode * right;
};

struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) {
    char *p;
    p = (char*)malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p,s);
    }
    return p;
}