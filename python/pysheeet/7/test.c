#include <stdio.h>
#include <stdlib.h>

// like oop in c
typedef struct Gen {
    int var;
    int (*next) (struct Gen*);
} gen;

int next(gen* g) {
    g->var += 1;
    return g->var;
}

gen* new() {
    gen* g = malloc(sizeof(gen));
    g->var = 0;
    g->next = next;
    return g;
}

int main(int argc, char* argv[]) {
    gen* g = new();
    for (int i = 0; i < 3; i++)
        printf("%d ", g->next(g));
    return 0;
}