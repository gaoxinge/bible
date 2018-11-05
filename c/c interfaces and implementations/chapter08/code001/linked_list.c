#include <stdio.h>

struct Node {
    struct Node *next;
    int value;
};

int main() {
    struct Node last   = {NULL, 3};
    struct Node medium = {&last, 2};
    struct Node first  = {&medium, 1};
    struct Node *root  = &first;
    
    struct Node *p;
    for (p = root; p; p = p->next) {
        printf("%d ", p->value);
    }
    
    struct Node **pp;
    for (pp = &root; *pp; pp = &(*pp)->next) {
        printf("%d ", (*pp)->value);
    }
    
    return 0;
}