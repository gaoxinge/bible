#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

#define T Stack_T

struct T {
    int count;
    struct elem {
        void *x;
        struct elem *link;
    } *head;
};

T Stack_new(void) {
    T stk;

    stk = malloc((long) sizeof(*stk));
    stk->count = 0;
    stk->head = NULL;
    return stk;
}

int Stack_empty(T stk) {
    assert(stk);  // make sure that stk is initialized
    return stk->count == 0;
}

void Stack_push(T stk, void *x) {
    struct elem *t;

    assert(stk);  // make sure that stk is initialized
    t = malloc((long) sizeof(*t));
    t->x = x;
    t->link = stk->head;
    stk->head = t;
    stk->count++;
}

void *Stack_pop(T stk) {
    void *x;
    struct elem *t;

    assert(stk);  // make sure that stk is initialized
    assert(stk->count > 0);  // make sure that stk has elements
    t = stk->head;
    stk->head = t->link;
    stk->count--;
    x = t->x;
    free(t);
    return x;
}

void Stack_free(T *stk) {
    struct elem *t, *u;

    assert(stk && *stk);  // make sure that *stk is initialized
    for (t = (*stk)->head; t; t = u) {
        u = t->link;
        free(t);
    }
    free(*stk);
}