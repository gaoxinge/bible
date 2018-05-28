#include <stdio.h>
#include <setjmp.h>
#include "parse.h"
#include "value.h"
#include "error.h"
#define BUFSIZE 1024

int main() {
    volatile int errors = 0;
    char buf[BUFSIZE];
    
    if (setjmp(onError))
        ++errors;
    
    while (gets(buf)) {
        if (scan(buf)) {
            void* e = sum();
            
            if (token)
                error("trash after sum");
            
            process(e);
            delete(e);
        }
    }
    
    return errors > 0;
}