#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = malloc(sizeof(int));
    int *b = a;
    printf("a: %p %p %d\n", &a, a, *a);
    printf("b: %p %p %d\n", &b, b, *b);

    *a = 1;
    printf("a: %p %p %d\n", &a, a, *a);
    printf("b: %p %p %d\n", &b, b, *b);

    free(b);
    printf("a: %p %p %d\n", &a, a, *a);
    printf("b: %p %p %d\n", &b, b, *b);

    return 0;
}