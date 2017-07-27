/* done accorging to the malloca tutorial pdf, target with 32 bit and 4-byte word machine  */
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_block *t_block;
struct s_block {
    size_t size;
    t_block next;
    int free; // 0 for being used, 1 for free
    char data[1]; // not count in to the struct size in the program. only used to get the tail address of this structure, meta-data
}; // struct no need to align, 12byte + 1
// for 8 byte word machine, the free and data shouldn't exist
// since structure should be 24 byte, or the address to put the chunk data will not be multiplier of 8.
// so data structure padding is a must here.

#define BLOCK_SIZE 12 /* can not use sizeof and minus because we don't know the actual padding size */
#define align(x) (((((x) - 1) >> 2) << 2) + 4)
#define WORD_SIZE 4 /* data alignment and data structure padding */

t_block base = NULL;

t_block find_block(t_block *last, size_t size) {
    t_block b = base;
    while (b && !(b->free && b->size >= size)) { // tranverse the entire link list every time called.
        *last = b;
        b = b->next;
    }
    /* if block found, the last is the previous block of the found one(return b), else the last is the last node in the link list (return NULL). */
    return b;
}

t_block extend_heap(t_block last, size_t size) {
    t_block b;
    b = sbrk(0);
    if (sbrk(BLOCK_SIZE + size) == (void *)-1)
        return NULL;
    b->size = size;
    b->next = NULL;
    b->free = 0;
    if (last)
        last->next = b;
    return b;
}

void split_block(t_block b, size_t s) {
    t_block new;
    new = (t_block) b->data + s; // b->data is char* type, so can use pointer addition with s bytes
    new->size = b->size-s-BLOCK_SIZE;
    new->next = b->next;
    new->free = 1;
    b->next = new;
    b->size = s;
}

void *malloc(size_t size) {
    t_block b, last;
    size_t s;
    s = align(size);
    if (base) {
        /* aleardy initialized */
        last = base;
        b = find_block(&last, s);
        if (b) {
            /* try to split the block */
            if ((b->size - s) >= (BLOCK_SIZE + WORD_SIZE))
                split_block(b, s);
            b->free = 0;
        } else {
            /* no block found, the last pointer points to the last node in the list, extend heap. */
            b = extend_heap(last, s);
            if (!b)
                return NULL;
        }
    } else {
        b = extend_heap(NULL, s);
        if (!b)
            return NULL;
        base = b;
    }
    return (b->data); // or (unsigned char *)b + BLOCK_SIZE
}


void *calloc(size_t num, size_t size) {
    size_t *new;
    size_t s4, i;
    new = malloc(num*size);
    if (new) {
        s4 = align(num*size) >> 2;
        for (i = 0; i < s4; i++)
            new[i] = 0;
    }
    return (new);// no need to convert to cha*, because type is void *
}

// free cuntion: find the previous and the next chunk, test if empty and merge them.
// To find the previous chunk, two methods: 1. maintain a hashtable to save the last node and the returned node
// 2. use double linked list