#include <stdio.h>
#include <stdlib.h>

// like oop in c
typedef struct Closure {
    int val;
    void (*add) (struct Closure*, int);
} closure;

void add(closure* c, int var) {
    c->val += var;
}

int main(int argc, char* argv[]) {
    closure* c = malloc(sizeof(closure));
    c->val = 5566;
    c->add = add;
    c->add(c, 9527);
    printf("%d\n", c->val);
    
    closure _c1 = {
        5566,
        add
    };
    closure* c1 = &_c1;
    c1->add(c1, 9527);
    printf("%d\n", c1->val);
    return 0;
}