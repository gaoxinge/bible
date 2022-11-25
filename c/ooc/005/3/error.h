#ifndef SETJMP_H
#include <setjmp.h>
#endif

#ifndef ERROR_H
#define ERROR_H

jmp_buf onError;
void error(const char* fmt, ...);

#endif