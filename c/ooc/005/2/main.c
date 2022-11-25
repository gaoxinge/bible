#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define NUMBER '1'

static jmp_buf onError;

enum tokens {NUM=NUMBER};
static enum tokens token;
static double number;

void error(const char*, ...);
static enum tokens scan(const char*);
static double sum();
static double product();
static double factor();

int main() {
    volatile int errors = 0;
    char buf[BUFSIZE];
    
    if (setjmp(onError))
        ++errors;
    
    while (gets(buf)) {
        if (scan(buf)) {
            double e = sum();
            
            if (token)
                error("trash after sum");
            
            printf("%f\n", e);
        }
    }
    
    return errors > 0;
}


// error handling
void error(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    putc('\n', stderr);
    va_end(ap);
    longjmp(onError, 1);
}


// tokenizer
static enum tokens scan(const char* buf) {
    static const char* bp;
    
    if (buf)
        bp = buf;
    
    while (isspace(*bp))
        ++bp;
    
    if (isdigit(*bp) || *bp == '.') {
        errno = 0;
        token = NUMBER, number = strtod(bp, (char**) &bp);
        if (errno == ERANGE)
            error("bad value: %s", strerror(errno));
    } else {
        token = *bp ? *bp++ : 0;
    }
    return token;
}


// parser

static double sum() {
    double result = product();
    
    for (;;) {
        switch (token) {
            case '+':
                scan(0);
                result += product();
                break;
            case '-':
                scan(0);
                result -= product();
                break;
            default:
                return result;
        }
    }
}

static double product() {
    double result = factor();
    
    for (;;) {
        switch (token) {
            case '*':
                scan(0);
                result *= factor();
                break;
            case '/':
                scan(0);
                result /= factor();
                break;
            default:
                return result;
        }
    }
}

static double factor() {
    double result;
    
    switch (token) {
        case '+':
            scan(0);
            return factor();
        case '-':
            scan(0);
            return -factor();
        case NUMBER:
            result = number;
            break;
        case '(':
            scan(0);
            result = sum();
            if (token != ')')
                error("excepting )");
            break;
        default:
            error("bad factor: '%c' 0x%x", token, token);
    }
    scan(0);
    return result;
}