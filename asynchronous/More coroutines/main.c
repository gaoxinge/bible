#include "picoro.h"
#include <stdio.h>


void *foo(void *arg) {
    int *p = arg;
    int  a = *p; 
    printf("foo %d\n", a);
    
    int  b = 2 * a;
    int *q = &b;
    return yield(q);
}


int main() {
    int a = 1;
    coro co = coroutine(foo);
    int *q = resume(co, &a);
    int  b = *q;
    printf("main %d\n", b);
    return 0;
}