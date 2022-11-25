#include <stdio.h>
#include <setjmp.h>

jmp_buf Buf;


void C() {
    if (setjmp(Buf) == 0)
        return;
    else
        printf("I am back\n");
}


void B() {
    C();
}


int main() {
    B();
    longjmp(Buf, 1);
    return 0;
}