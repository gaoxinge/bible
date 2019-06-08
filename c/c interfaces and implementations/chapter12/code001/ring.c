#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <asser.h>
#include "ring.h"

#define T Ring_T

struct T {
    struct node {
        struct node *llink, *rlink;
        void *value;
    } *head;
    int length;
};

T Ring_new() {
    T ring = malloc(sizeof(*ring));
    ring->head = NULL;
    return ring;
}

T Ring_ring(void *x, ...) {
    va_list ap;
    T ring = Ring_new();
    va_start(ap, x);
    for (; x; x = va_arg(ap, void *))
        Ring_addhi(ring, x);
    va_end(ap);
    return ring;
}