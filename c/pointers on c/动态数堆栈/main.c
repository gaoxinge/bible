#include "stack.h"
#include <stdio.h>

int main() {
    create_stack(3);
    
    push(1);
    push(2);
    push(3);
    
    pop();
    
    printf("%d\n", top());
    printf("%d\n", is_empty());
    printf("%d", is_full());
    
    destroy_stack();
    
    return 0;
}