#include <stdio.h>

#define MAP(func, src, dst, len)               \
    do {                                       \
        for (unsigned i = 0; i < len; i++) {   \
            dst[i] = func(src[i]);             \
        }                                      \
    } while (0);                               \
    
int multi2(int a) {
    return 2 * a;
}

int main(int argc, char* argv[]) {
    int x[] = {1, 2, 3, 4, 5};
    int y[5];
    MAP(multi2, x, y, 5);
    for (unsigned i = 0; i < 5; i++) {
        printf("%d ", y[i]);
    }
    return 0;
}