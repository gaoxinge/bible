/* simple dynamic array, inspired by
 * https://github.com/antirez/sds */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *assign_N(void *s, size_t N) {
    size_t *n = s;
    *n = N;
    return n + 1;
}

/* create sda with type T and length N */
#define sdanew(T, N) assign_N(malloc(sizeof(struct {size_t n; T a[];}) + N * sizeof(T)), N)

/* get length of sda */
size_t sdalen(void *a) {
    size_t *n = a;
    n -= 1;
    return *n;
}

/* delete sda, free the memory of the 
 * sda */
void sdadelete(void *a) {
    size_t *n = a;
    n -= 1;
    free(n);
}

int main() {
    float *a = sdanew(float, 3);
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;
    printf("%d", sdalen(a));
    free(a);
    return 0;
}