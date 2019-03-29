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

### parent process

- [How Linux Process Life Cycle Works – Parent, Child, and Init Process](https://www.thegeekstuff.com/2013/07/linux-process-life-cycle/)

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

## reference

- [apue](http://www.apuebook.com/)