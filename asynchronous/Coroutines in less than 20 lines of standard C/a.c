#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

#define STACKDIR -
#define STACKSIZE (1 << 12)
#define MAXTHREAD 10

static void *coarg;
static char *tos;
static jmp_buf thread[MAXTHREAD];
static int count = 0;

void *coto(jmp_buf here, jmp_buf there, void *arg) {
    coarg = arg;
    if (setjmp(here)) return(coarg);
    longjmp(there, 1);
}

void *cogo(jmp_buf here, void (*fun)(void *), void *arg) {
    if (tos == NULL) tos = (char *) &arg;
    printf("old address of tos: %p\n", tos);
    tos += STACKDIR STACKSIZE;
    char n[STACKDIR(tos - (char *) &arg)];
    printf("new address of tos: %p\n", tos);

    coarg = n;
    if (setjmp(here)) return(coarg);
    fun(arg);
    abort();
}

static void comain(void *arg) {
    int *p = arg;
    int i = *p;
    for (;;) {
        printf("coroutine %d at %p, p %p arg %p\n", i, &i, p, arg);
        int n = rand() % count;
        printf("jumping from %d to %d\n", i, n);
        arg = coto(thread[i], thread[n], (char *) arg + 1);
    }
}

int main() {
    while (++count < MAXTHREAD) {
        printf("\nspawning %d\n", count);
        coarg = cogo(thread[0], comain, &count);
        printf("address of coarg: %p\n", coarg);
    }
    return 0;
}