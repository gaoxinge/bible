#include <stdio.h>
#include <stdlib.h>

int main() {
    int *b = malloc(sizeof(int));
    int *a = b;
    printf("a: %p %p %d\n", &a, a, *a);  // a: 0061FF28 00C616D8 12981888
    printf("b: %p %p %d\n", &a, a, *a);  // b: 0061FF28 00C616D8 12981888

    *a = 1;
    printf("a: %p %p %d\n", &a, a, *a);  // a: 0061FF28 00C616D8 1
    printf("b: %p %p %d\n", &a, a, *a);  // b: 0061FF28 00C616D8 1

    return 0;
}