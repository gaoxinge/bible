#include <ucontext.h>
#include <stdio.h>

#define MAX_COUNT (1 << 5)

static ucontext_t uc[3];
static int count = 0;

void ping();
void pong();

void ping() {
    while (count < MAX_COUNT) {
        printf("ping %d\n", ++count);
        swapcontext(&uc[1], &uc[2]);
    }
}

void pong() {
    while (count < MAX_COUNT) {
        printf("pong %d\n", ++count);
        swapcontext(&uc[2], &uc[1]);
    }
}

char st1[8192];
char st2[8192];

int main(int argc, char *argv[]) {
    getcontext(&uc[1]);
    uc[1].uc_link = &uc[0];
    uc[1].uc_stack.ss_sp = st1;
    uc[1].uc_stack.ss_size = sizeof(st1);
    makecontext(&uc[1], ping, 0);
    
    getcontext(&uc[2]);
    uc[2].uc_link = &uc[0];
    uc[2].uc_stack.ss_sp = st2;
    uc[2].uc_stack.ss_size = sizeof(st2);
    makecontext(&uc[2], pong, 0);
    
    swapcontext(&uc[0], &uc[1]);
    return 0;
}