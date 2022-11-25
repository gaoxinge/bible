#include "apue.h"

static void sig_usr(int);

int main() {
    struct sigaction sa1;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_handler = sig_usr;
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);
    
    struct sigaction sa2;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_handler = sig_usr;
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);
    
    for (;;)
        pause();
    return 0;
}

static void sig_usr(int signo) {
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        err_dump("received signal %d\n", signo);
}