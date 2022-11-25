#include "stack.h"
#include <stdio.h>

int main() {
    push(1);
    push(2);
    push(3);
    
    pop();
    
    printf("%d\n", top());
    printf("%d\n", is_empty());
    printf("%d", is_full());
    
    return 0;
}