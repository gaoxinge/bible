#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#define T List_T

// add right
T List_append(T list, T tail) {
    T *p = &list;
    while (*p)
        p = &(*p)->rest;
    *p = tail;
    return list;
}

// from left to right
T List_copy(T list) {
    T head, *p = &head;
    
    for (; list; list = list->rest) {
        *p = malloc(sizeof(**p));
        (*p)->first = list->first;
        p = &(*p)->rest;
    }
    *p = NULL;
    return head;
}

// from left to right
T List_list(void *x, ...) {
    va_list ap; 
    T list, *p = &list;  // p is used to traversal 
    
    va_start(ap, x);
    for (; x; x = va_arg(ap, void *)) {
        *p = malloc(sizeof(**p));
        (*p)->first = x;
        p = &(*p)->rest;
    }
    *p = NULL;
    va_end(ap);
    return list;
}

// remove left
T List_pop(T list, void **x) {
    if (list) {
        T head = list->rest;
        if (x)
            *x = list->first;
        free(list);
        return head;
    } else {
        return list;
    }
}

// add left
T List_push(T list, void *x) {
    T p = malloc(sizeof(*p));
    p->first = x;
    p->rest = list;
    return p;
}

// from left to right
T List_reverse(T list) {
    T head = NULL, next;
    
    for (; list; list = next) {
        next = list->rest;
        list->rest = head;
        head = list;
    }
    return head;
}

// from left to right
int List_length(T list) {
    int n = 0;
    
    for (; list; list = list->rest) 
        n++;
    return n;
}

// fromt left to right
void List_free(T *list) {
    T next;
    
    assert(list);
    for (; *list; *list = next) {
        next = (*list)->rest;
        free(*list);
    }
}

// from left to right
void List_map(T list, void apply(void **x, void *cl), void *cl) {
    assert(apply);
    for (; list; list = list->rest)
        apply(&list->first, cl);
}

// from left to right
void **List_toArray(T list, void *end) {
    int i, n = List_length(list);
    void **array = malloc((n + 1) * sizeof(*array));
    
    for (i = 0; i < n; i++) {
        array[i] = list->first;
        list = list->rest;
    }
    array[i] = end;
    return array;
}