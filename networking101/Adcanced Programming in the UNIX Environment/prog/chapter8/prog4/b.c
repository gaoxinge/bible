#include "apue.h"
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execl("/gxg/prog/chapter8/prog4/testinterp", "testinterp", "myarg1", "MY ARG2", NULL) < 0)
            err_sys("execl error");
    }
    
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid error");
    
    return 0;
}