#include "stack.h"
#include <stdio.h>

int main() {
    int a = 1;
    float b = 2;
    
    Stack_T stack = Stack_new();
    printf("%d\n", Stack_empty(stack));
    
    void *t = &a;
    Stack_push(stack, t);
    printf("%d\n", Stack_empty(stack));
    
    t = &b;
    Stack_push(stack, t);
    printf("%d\n", Stack_empty(stack));
    
    t = Stack_pop(stack);
    printf("%.1f\n", * (float *) t);
    printf("%d\n", Stack_empty(stack));
    
    Stack_free(&stack);
    return 0;
}