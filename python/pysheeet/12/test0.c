#include <stdio.h>
#include <string.h>
#include <setjmp.h>

static jmp_buf jmp_ping, jmp_pong;
void ping();
void pong();


void ping() {
    int r = 0;
    
    r = setjmp(jmp_ping);
    if (r == 0) pong();
    printf("ping %d\n", r);
    
    r = setjmp(jmp_ping);
    if (r == 0) longjmp(jmp_pong, 20001);
    
    printf("ping %d\n", r);
    
    r = setjmp(jmp_ping);
    if (r == 0) longjmp(jmp_pong, 20002);
}

void pong() {
    int r = 0;
    
    r = setjmp(jmp_pong);
    if (r == 0) longjmp(jmp_ping, 10001);
    
    printf("ping %d\n", r);
    
    r = setjmp(jmp_pong);
    if (r == 0) longjmp(jmp_ping, 10002);
    
    printf("pong %d\n", r);
}

int main(int argc, char* argv[]) {
    ping();
    return 0;
}