#include <stdio.h>
#include <stdlib.h>

void f(int *b) {
    printf("b: %p %p %d\n", &b, b, *b);  // b: 0061FF10 00400080 17744
    b = malloc(sizeof(int));
    printf("b: %p %p %d\n", &b, b, *b);  // b: 0061FF10 007116D8 7411328
}

int main() {
    int *a;
    printf("a: %p %p %d\n", &a, a, *a);  // a: 0061FF2C 00400080 17744
    
    f(a);
    printf("a: %p %p %d\n", &a, a, *a);  // a: 0061FF2C 00400080 17744

    *a = 1;                              // error: the value of a is not initialized
    printf("a: %p %p %d\n", &a, a, *a);
    return 0;
}