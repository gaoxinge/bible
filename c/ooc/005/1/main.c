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
static void print_token();

int main() {
    volatile int errors = 0;
    char buf[BUFSIZE];
    
    if (setjmp(onError))
        ++errors;
    
    while (gets(buf)) {
        if (scan(buf)) {
            print_token();
            
            while (scan(0))
                print_token();
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

static void print_token() {
    if (token == NUMBER) {
        printf("NUM %f\n", number);
    } else {
        switch (token) {
            case '+':
                printf("ADD\n");
                break;
            case '-':
                printf("SUB\n");
                break;
            case '*':
                printf("MUL\n");
                break;
            case '/':
                printf("DIV\n");
                break;
            case '(':
                printf("LPAREN\n");
                break;
            case ')':
                printf("RPAREN\n");
                break;
            default:
                printf("ERROR %c\n", token);
        }
    }
}


