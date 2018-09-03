#include <stdio.h>
#include <stdlib.h>

void f(int **t) {
    *t = malloc(sizeof(int));
}

int main() {
    int *a;
    f(&a);
    printf("a: %p %p %d\n", &a, a, *a);

    *a = 1;
    printf("a: %p %p %d\n", &a, a, *a);

    return 0;
}