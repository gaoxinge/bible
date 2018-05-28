#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include "error.h"

jmp_buf onError;

void error(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    putc('\n', stderr);
    va_end(ap);
    longjmp(onError, 1);
}