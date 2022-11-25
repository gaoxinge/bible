#include <stdio.h>
#include <setjmp.h>

jmp_buf Buf1, Buf2;


void C() {
    if (setjmp(Buf2) == 0)
        longjmp(Buf1, 1);
    else
        printf("I am back\n");
}


void B() {
    C();
}


int main() {
    if (setjmp(Buf1) == 0) 
        B();
    else                   
        longjmp(Buf2, 1);
    return 0;
}