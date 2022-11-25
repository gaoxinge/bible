#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "except.h"

Except_T Allocate_Failed = { "Allocation failed" };

void *allocate(unsigned n) {
    void *new = malloc(n);
    
    if (new)
        return new;
    RAISE(Allocate_Failed);
    assert(0);
}

int main() {
    char *buf;
    TRY
        buf = allocate(4096);
    EXCEPT(Allocate_Failed)
        fprintf(stderr, "couldn't allocate the buffer\n");
        exit(EXIT_FAILURE);
    END_TRY;
}