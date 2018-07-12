#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#define STACK_SIZE 100

static STACK_TYPE *stack;
static int stack_size;
static int top_element = -1;

void create_stack(int size) {
    assert(stack_size == 0);
    stack_size = size;
    stack = malloc(stack_size * sizeof(STACK_TYPE));
    assert(stack != NULL);
}

void destroy_stack() {
    assert(stack_size > 0);
    stack_size = 0;
    free(stack);
}

void push(STACK_TYPE value) {
    assert(!is_full());
    top_element += 1;
    stack[top_element] = value;
}

void pop() {
    assert(!is_empty());
    top_element -= 1;
}

STACK_TYPE top() {
    assert(!is_empty());
    return stack[top_element];
}

int is_empty() {
    assert(stack_size > 0);
    return top_element == -1;
}

int is_full() {
    assert(stack_size > 0);
    return top_element == STACK_SIZE - 1;
}