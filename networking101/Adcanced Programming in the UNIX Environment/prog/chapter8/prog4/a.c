#include "apue.h"
#include <sys/wait.h>

char *env_init[] = {
    "USER=unknown",
    "PATH=/tmp",
    NULL
};

int main() {
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execle("/gxg/echoall", "echoall", "myarg1", "MY ARG2", NULL, env_init) < 0)
            err_sys("execle error");
    }
    
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");
    
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execlp("echoall", "echoall", "only 1 arg", NULL) < 0)
            err_sys("execlp error");
    }
    
    return 0;
}