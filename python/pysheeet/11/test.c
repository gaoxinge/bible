#include <stdio.h>
#include <string.h>
#include <setjmp.h>

enum {
    ERR_EPERM = 1,
    ERR_ENOENT,
    ERR_ESRCH,
    ERR_EINTR,
    ERR_EIO
};

#define try                                 \
    do {                                    \
        jmp_buf jmp_env__;                  \
        switch (setjmp(jmp_env__)) {        \
            case 0:                         \
                while(1) {                  \

#define raise(exc)                          \
                    longjmp(jmp_env__, exc) \
                
#define except(exc)                         \
                    break;                  \
                    case exc:               \

#define finally                             \
                    break;                  \
                }                           \
            default:                        \

#define end                                 \
        }                                   \
    } while (0)                             \
    
    
int main(int argc, char* argv[]) {
    int ret = 0;
    
    try {
        raise(ERR_ENOENT);
    } except(ERR_EPERM) {
        printf("get exception: %s\n", strerror(ERR_EPERM));
        ret = -1;
    } except(ERR_ENOENT) {
        printf("get exception: %s\n", strerror(ERR_ENOENT));
        ret = -1;
    } except(ERR_ESRCH) {
        printf("get exception: %s\n", strerror(ERR_ESRCH));
    } finally {
        printf("finally block\n");
    } end;
    
    return ret;
}
