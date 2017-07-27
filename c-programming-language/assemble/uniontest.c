#include <stdio.h>
#include <stdlib.h>

union U1
{
    char s[9];
    int n;
    double d;
};

union U2
{
    char s[5];
    int n;
    double d;
};

typedef long Align;
union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};
typedef union header Header;

typedef struct s_block *t_block;
struct s_block {
    size_t size;
    t_block next;
    int free; // 0 for being used, 1 for free
};

struct S{
    int a; // 8 byte
    double b; // 8 byte
    int *ptr;
    char data[1];
};

int main(int argc, char *argv[])
{
    Header h;
    printf("Header: %lu\n", sizeof(h)); //16
    printf("Align: %lu\n", sizeof(h.x)); //8
    printf("struct: %lu\n", sizeof(h.s)); //16
    printf("struct ptr: %lu\n", sizeof(h.s.ptr)); //8
    printf("struct size: %lu\n\n", sizeof(h.s.size)); //4

    struct s_block sb;
    printf("sblock size: %lu\n", sizeof sb);

    union U1 u1;
    union U2 u2;
    printf("%lu\n",sizeof(u1)); 
    printf("%lu\n",sizeof(u2));
    printf("%p\n",&u1);
    printf("%p\n",&u1.s);
    printf("%p\n",&u1.n);
    printf("%p\n",&u1.d);
    u1.n=1;
    printf("%d\n",u1.s[0]); // 1
    printf("%lf\n",u1.d); // 0
    unsigned char *p=(unsigned char *)&u2;
    printf("%d\n",*p);
    printf("%d\n",*(p+1));
    printf("%d\n",*(p+2));
    printf("%d\n",*(p+3));
    printf("%d\n",*(p+4));
    printf("%d\n",*(p+5));
    printf("%d\n",*(p+6));
    printf("%d\n",*(p+7));
    printf("%d\n",*(p+8));// 0
    printf("%d\n",*(p+9));
    printf("%d\n",*(p+10));
    printf("%d\n",*(p+11));
    printf("%d\n",*(p+12));
    printf("%d\n",*(p+13));
    printf("%d\n",*(p+14));
    printf("%d\n",*(p+15));
    union U2 * u2p = &u2;
    printf("\n\n");

    struct S s;
    printf("%p\n", &s.b);
    printf("%p\n", s.ptr);
    printf("%p\n\n", s.data);
    struct S *sp = malloc(sizeof(struct S));
    printf("size: %lu\n", sizeof s);
    printf("%p\n", sp);
    printf("%p\n", &sp->a);
    printf("%p\n", &sp->b);
    printf("%lu\n", (unsigned char *)&sp->b - (unsigned char *)&sp->a);
    printf("%p\n", &sp->ptr);
    printf("%p\n", sp->data);
    // printf("%d\n", );
    return 0;
}