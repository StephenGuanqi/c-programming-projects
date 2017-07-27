#include <stdio.h>

typedef unsigned char *byte_p;

void show_bytes(byte_p start,int len){
    for(int i=0;i < len;i++)
        printf(" %.2x",start[i]);
    printf("\n");
}

void show_int(int x){
    show_bytes((byte_p) &x,sizeof(int));
}

void show_float(float x){
    show_bytes((byte_p) &x,sizeof(float));
}

void show_pointer(void *x){
    show_bytes((byte_p) &x,sizeof(void *));
}

void test3(){
    int val=0x87654321;

    byte_p valp=(byte_p)&val;
    show_bytes(valp,4);
    show_int(val);

    float val1=0x4A564504; //3510593
    show_float(val);

    printf(" %p\n",&val);
    show_pointer(&val);
}

int main(){
    test3();
    //小端法：21 43 65 87(低地址低字节序列)
    //大端法：87 65 43 21(低地址高字节序列)
    return 0;
}