#include <stdio.h>
#define SWAP(t, x, y) t tmp = x; x = y; y = tmp
#define dprint(expr) printf(#expr "= %d \n", expr)

int main() {
    int x = 1;
    int y = 2;
    SWAP(int, x, y);
    dprint(x);
    dprint(y);
    dprint(x/y);
    return 0;
}