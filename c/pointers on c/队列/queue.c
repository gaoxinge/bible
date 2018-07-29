#include "queue.h"
#include <stdio.h>
#include <assert.h>

#define QUEUE_SIZE 100
#define ARRAY_SIZE (QUEUE_SIZE + 1)

static QUEUE_TYPE queue[ARRAY_SIZE];
static int front = 1;
static int rear  = 0;


void insert(QUEUE_TYPE value) {
    assert(!is_full());
    rear = (rear + 1) % ARRAY_SIZE;
    queue[rear] = value;
}

void delete() {
    assert(!is_empty());
    front = (front + 1) % ARRAY_SIZE;
}

QUEUE_TYE first() {
    assert(!is_empty());
    return queue[front];
}

int is_empty() {
    return (rear + 1) % ARRAY_SIZE == front;
}

int is_full() {
    return (rear + 2) % ARRAY_SIZE == front;
}