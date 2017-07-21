#include <stdlib.h>
#include <string.h>

struct nlist {
    char *name;
    char *defn;
    struct nlist *next;
};

struct node {
    void *key;
    void *val;
    struct node *next;
};

#define HASHSIZE 101
struct nlist *hashtable[HASHSIZE];

struct nlist *lookup(char *);// get method
struct nlist *install(char *, char *); // put method
void undef(char *);

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s; s++) 
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *p;
    for (p = hashtable[hash(s)]; p != NULL; p = p->next)
        if (strcmp(p->name, s) == 0)
            return p;
    return NULL;
}

char *mystrdup(char *);

struct nlist *install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name))== NULL) {
        np = (struct nlist *)malloc(sizeof(struct nlist));// not enough, didn't check if valid
        // when using malloc, check each of the pointer in the struct is allocated with enough space
        if (np == NULL || (np->name = mystrdup(name)) == NULL) 
            return NULL;
        // np->name = name; // ???? wrong again!!!
        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;
    } else 
        free((void *)np->defn);
    if ((np->defn = mystrdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name) {
    struct nlist *current;
    struct nlist *previous;
    for (current = hashtable[hash(name)]; current != NULL; previous = current, current = current->next) 
        if ((strcmp(current->name, name)) == 0) {
            if (previous == NULL) // the found item is the HEAD node in the link list
                hashtable[hash(name)] = current->next;
            else 
                previous->next = current->next;
            free(current->name);
            free(current->defn);
            free(current);
            return;
        }
    return;
}