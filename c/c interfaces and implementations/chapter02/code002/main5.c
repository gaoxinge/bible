#include <stdio.h>
#include <stdlib.h>

int *f() {
    return malloc(sizeof(int));
}

int main() {
    int *a = f();
    printf("a: %p %p %d\n", &a, a, *a);

    *a = 1;
    printf("a: %p %p %d\n", &a, a, *a);

    return 0;
}