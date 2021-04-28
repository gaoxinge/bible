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

### reference

- [How Linux Process Life Cycle Works – Parent, Child, and Init Process](https://www.thegeekstuff.com/2013/07/linux-process-life-cycle/)
- [LINUX 的僵尸(ZOMBIE)进程](https://coolshell.cn/articles/656.html)

## signal

### interrupted system call

- [Difference between slow system calls and fast system calls](https://unix.stackexchange.com/questions/14293/difference-between-slow-system-calls-and-fast-system-calls)
- [慢系统调用引起的signal无效问题](http://xiaorui.cc/2017/07/19/%E6%85%A2%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8%E5%BC%95%E8%B5%B7%E7%9A%84signal%E6%97%A0%E6%95%88%E9%97%AE%E9%A2%98/)
- [慢系统调用与信号](https://www.cnblogs.com/diegodu/p/3973080.html)
- [8.Common Questions](http://beej.us/guide/bgnet/html/multi/faq.html)

### kill

- [kill与kill -9的区别](https://blog.csdn.net/u010486679/article/details/78415666)

### system v

- [10.4. Unreliable Signals](http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch10lev1sec4.html#ch10lev1sec4)
- [10.7. SIGCLD Semantics](http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch10lev1sec7.html)

## reference

- [apue](http://www.apuebook.com/)
