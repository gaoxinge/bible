## command

```
# cd lib
# gcc -c *.c -I ../include
# ar rsc apue.a *.o
```

```
# gcc -o main -I include prog/chapter1/prog1.c lib/apue.a
```

## vfs

- [inode](https://en.wikipedia.org/wiki/Inode)
- [Class 9: The Unix FileSystem](https://www.usna.edu/Users/cs/wcbrown/courses/IC221/classes/L09/Class.html)
- [File I/O](http://man7.org/training/download/lusp_fileio_slides.pdf)
- [VFS文件系统结构分析](http://blog.jobbole.com/105537/)
- [What exactly is the FILE keyword in C?](https://stackoverflow.com/questions/5672746/what-exactly-is-the-file-keyword-in-c)
- [I Wanna know the Internal Members of struct FILE, the latest ones](https://stackoverflow.com/questions/17209087/i-wanna-know-the-internal-members-of-struct-file-the-latest-ones)

## process

- session: 会话/id/终端,shell
- process group: 进程组/id/管道
- parent process: 父进程/ppid
- process: 进程/pid

### session

- exit/ctrl-d: EOF, not signal. But send SIGHUP signal to jobs

### foreground process and background process

- session: one foreground process and many background process
- command: foreground process
- command &: background process
- nohup command: foreground process, ignore SIGHUP signal
- nohup command &: background process, ignore SIGHUP signal
- ctrl-c: cancel or exit a foreground process, send SIGINT
- ctrl-\\: cancel or exit a foreground process, send SIGQUIT
- ctrl-z: stop a foreground process, send SIGTSTP
- jobs: process in session with job id
- fg %jobid: turn foreground process with jobid to background process
- bg %jobid: turn background process with jobid to foreground process
- disown: move jobs from session to outside

### init process

- pid: 1
- ppid: 0

### parent process

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("%ld %ld\n", (long) getpid(), (long) getppid());  // 8260 8222
}
```

```
# ps -eLf
# UID        PID  PPID   LWP  C NLWP STIME TTY          TIME CMD
# root      8222     0  8222  0    1 01:34 pts/1    00:00:00 bash
```

### zombie process

- 一个子进程exit会成为僵尸进程
- 如果父进程调用wait或者waitpid，可以回收子进程
- 如果父进程不调用wait或者waitpid，也不结束，子进程将一直处于僵尸进程。这种情况下需要调用kill -9杀死父进程，使得子进程过继给init进程
- 如果父进程结束，子进程将会过继给init进程

### orphan process

- 父进程退出，子进程过继给init进程

### daemon process

- 守护进程是一种特殊的孤儿进程

### reference

- [linux进程组、会话以及任务管理](https://andrewpqc.github.io/2018/10/31/linux-process-group-and-session-and-jobs-manage/)
- [linux后台执行命令：&与nohup的用法](https://zhuanlan.zhihu.com/p/59297350)
- [Linux - 请允许我静静地后台运行](https://zhuanlan.zhihu.com/p/32254479)
- [linux 在终端打开程序后关闭终端，程序也跟着关闭了怎么办？](https://www.zhihu.com/question/442188249)
- [How Linux Process Life Cycle Works – Parent, Child, and Init Process](https://www.thegeekstuff.com/2013/07/linux-process-life-cycle/)
- [LINUX 的僵尸(ZOMBIE)进程](https://coolshell.cn/articles/656.html)
- [戏说守护、僵尸、孤儿进程](https://zhuanlan.zhihu.com/p/21250530)
- [Python实现守护进程](https://zhuanlan.zhihu.com/p/25118420)
- [计算机daemon和通过死循环构造的进程的区别是什么？](https://www.zhihu.com/question/385503175)

## signal

### interrupted system call

- [Difference between slow system calls and fast system calls](https://unix.stackexchange.com/questions/14293/difference-between-slow-system-calls-and-fast-system-calls)
- [慢系统调用引起的signal无效问题](http://xiaorui.cc/2017/07/19/%E6%85%A2%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8%E5%BC%95%E8%B5%B7%E7%9A%84signal%E6%97%A0%E6%95%88%E9%97%AE%E9%A2%98/)
- [慢系统调用与信号](https://www.cnblogs.com/diegodu/p/3973080.html)
- [8.Common Questions](http://beej.us/guide/bgnet/html/multi/faq.html)

### kill

- [kill与kill -9的区别](https://blog.csdn.net/u010486679/article/details/78415666)
- [24.2.2 Termination Signals](https://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html)
- SIGHUP: kill -1
- SIGINT: kill -2/ctrl-c
- SIGQUIT: kill -3/ctrl-\\
- SIGTERM: kill/kill -15
- SIGKILL: kill -9

### system v

- [10.4. Unreliable Signals](http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch10lev1sec4.html#ch10lev1sec4)
- [10.7. SIGCLD Semantics](http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch10lev1sec7.html)

## reference

- [apue](http://www.apuebook.com/)
