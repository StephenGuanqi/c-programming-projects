#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode * right;
};

typedef struct node *TreeNodePtr;
typedef struct node{
    char *word;
    int count;
    TreeNodePtr left;
    TreeNodePtr right;
}TreeNode;

struct tnode *addtree(struct tnode *, char *);
void addtree2(struct tnode **, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) 
        if (isalpha(word[0]))
            // root = addtree(root, word);
            addtree2(&root, word);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/* add a node at p position or below the p position */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {
        p = talloc();
        // p -> word = w;// be careful!!!!!
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) 
        p->count++;
    else if (cond > 0) 
        p->right = addtree(p->right, w);
    else
        p->left = addtree(p->left, w);
    return p;
}

void addtree2(struct tnode **p, char *w) {
    int cond = 0;
    if (*p == NULL) {
        *p = talloc();
        (*p)->word = mystrdup(w);
        (*p)->count = 1;
        (*p)->left = (*p)->right = NULL;
    } else if ((cond = strcmp(w, (*p)->word)) == 0)
        (*p)->count++;
    else if (cond > 0)
        addtree2(&(*p)->right, w);
    else 
        addtree2(&(*p)->left, w);
    return;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}