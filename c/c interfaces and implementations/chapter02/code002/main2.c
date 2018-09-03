#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a;
    int *b = a;                          // the addresss of b is different from a, but the value of b is the same as a 
    printf("a: %p %p %d\n", &a, a, *a);  // a: 0061FF2C 00400080 17744
    printf("b: %p %p %d\n", &b, b, *b);  // b: 0061FF28 00400080 17744
    
    b = malloc(sizeof(int));             // the value of b is initialized, and different from a
    printf("a: %p %p %d\n", &a, a, *a);  // a: 0061FF2C 00400080 17744
    printf("b: %p %p %d\n", &b, b, *b);  // b: 0061FF28 001316D8 1250944
    
    *a = 1;                              // error: the value of a is not initialized
    printf("a: %p %p %d\n", &a, a, *a);
    printf("b: %p %p %d\n", &b, b, *b);
    return 0;
}