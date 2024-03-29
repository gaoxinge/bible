## string literal

- [C语言中字符串常量的好处在哪里](https://www.zhihu.com/question/20779337)

```c
#include <stdio.h>

int main() {
    int a = 1;
    int *b = &a;
    int *c = b;
    
    printf("*b = %d, b = %p, &b = %p\n", *b, b, &b);
    printf("*c = %d, c = %p, &c = %p\n", *c, c, &c);
    
    char *mesg = "Don't be a fool!";
    char *copy = mesg;
    
    printf("value = %s, mesg = %p, &mesg = %p\n", mesg, mesg, &mesg);
    printf("value = %s, copy = %p, &copy = %p\n", copy, copy, &copy);
    return 0;
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *p1 = "hello world";
    printf("value = %s, p1 = %p\n", p1, p1);
    
    char p2[] = "hello world";
    printf("%s\n", p2);
    p2[1] = 'a';
    printf("%s\n", p2);
    
    char *p3 = (char *) malloc(sizeof(char)*12);
    p3 = "hello world";
    printf("value = %s, p3 = %p\n", p3, p3);
    
    char *p4 = (char *) malloc(sizeof(char)*12);
    strcpy(p4, "hello world");
    printf("value = %s, p4 = %p\n", p4, p4);
    
    return 0;
}
```

## 结构体变量的声明

```c
#include <stdio.h>

struct Book {
    int id;
    char *name;
};

union u_tag {
    int ival;
    float fval;
    char *sva;
};

int main() {
    struct Book book;
    struct Book2 {
        int id;
        char *name;
    } book2;
    
    union u_tag tag;
    union u {
        int ival;
        float fval;
        char *sva;
    } t;
    return 0;
}
```

```c
#include <stdio.h>

// 初始化book
struct {
    char *name;
} book;

int main() {
    book.name = "abc";
    printf("%s", book.name);
    return 0;
}
```

```c
#include <stdio.h>

// 定义结构体类型struct Booky
struct Booky {
    char *name;
};

int main() {
    struct Booky book;
    book.name = "abc";
    printf("%s", book.name);
    return 0;
}
```

```c
#include <stdio.h>

// 初始化book
struct Booky {
    char *name;
} book;

int main() {
    book.name = "abc";
    printf("%s", book.name);
    return 0;
}
```

```c
#include <stdio.h>

// 定义结构体类型Book
typedef struct Booky {
    char *name;
} Book;

int main() {
    Book book;
    book.name = "abc";
    printf("%s", book.name);
    return 0;
}
```

## 八进制

```c
#include <stdio.h>
#define KEYWORD  01
#define EXTERNAL 02
#define STATIC   04

int main() {
    enum {keyword = 01, external = 02, statics = 04};
    
    printf("%d", KEYWORD);
    printf("%d", EXTERNAL);
    printf("%d", STATIC);
    
    printf("%d", keyword);
    printf("%d", external);
    printf("%d", statics);
    return 0;
}
```

## 格式化输出

```c
#include <stdio.h>

int main() {
    char *c = "%s\n";
    printf(c);                // ?@@
    printf(c, "hello world"); // hello world
    return 0;
}
```

## sizeof

```c
#include <stdio.h>
int f(int *);

int main() {
    int a;
    printf("%d\n", sizeof(a));
    printf("%d\n", sizeof(int));
    
    int b[3];
    printf("%d\n", sizeof(b));
    
    int n = 3;
    int c[n];
    printf("%d\n", sizeof(c));
    
    int d[] = {1, 2, 3};
    printf("%d\n", f(d));
    return 0;
} 

int f(int *a) {
    int sum = 0;
    int n = sizeof(a);
    int m = sizeof(a[0]);
    printf("n=%d, m=%d\n", n, m);
    for (int i = 0; i < n / m; ++i)
        sum += i;
    return sum;
}
```

## 文件描述符

- [File descriptor](https://en.wikipedia.org/wiki/File_descriptor)
- [每天进步一点点——Linux中的文件描述符与打开文件之间的关系](http://blog.csdn.net/cywosp/article/details/38965239)
- [Linux文件描述符](https://www.jianshu.com/p/430340c4a37a)
- [How do you read from stdin in Python?](https://stackoverflow.com/questions/1450393/how-do-you-read-from-stdin-in-python)

每个进程都维护这一张文件描述符表

```python
import sys
print(sys.stdin)    # 0
print(sys.stdout)   # 1
print(sys.stderr)   # 2
f = open('test.py')
print(f.fileno())   # 3
```

### 重定向

改变了进程默认的stdin，stdout

- stdin：`prog < infile`
- stdout：`prog > infile`

## 管道

- [How to get file descriptor of buffer in memory?](https://stackoverflow.com/questions/1558772/how-to-get-file-descriptor-of-buffer-in-memory)

pipe左侧的进程的stdout指向pipe，右侧的进程的stdin指向pipe

- `prog | anotherprog`

```python
import os
r, w = os.pipe()
r = os.fdopen(r)
print(r.fileno()) # 3
w = os.fdopen(w)
print(w.fileno()) # 4 
```

## 系统调用

- [system call](https://en.wikipedia.org/wiki/System_call)

### windows

- [How to start programming in Windows?](https://stackoverflow.com/questions/5125431/how-to-start-programming-in-windows)
- [theForger's Win32 API Programming Tutorial](http://www.winprog.org/tutorial/)
- [windows programming](https://github.com/gaoxinge/bible/blob/master/c/the%20c%20programming%20language/windows%20programming.pdf)

windows编程/windows环境编程：系统调用api（win32 api）通过动态链接库（dll）实现

- msc：windows环境，windows api
- mingw：windows环境，linux api
- cygwin：linux环境，linux api

### linux

linux编程/linux环境编程：系统调用api通过libc（c library）实现，比如glibc（gnu c library）

#### unistd

```c
#include <unistd.h>
#include <stdio.h>
#define BUFSIZE 3

/****************************
 * 进入显示start，退出显示end
 * 
 * write函数
 * 作用：将stdin中反复读入
 *      BUFSIZE个字符，放
 *      入buf里
 * 触发条件：回车，且回车也
 *      计入stdin里
 ****************************/
int main() {
    char buf[BUFSIZE];
    int n;
    
    printf("%s\n", "start");
    while ((n = read(0, buf, BUFSIZE)) > 0) {
        printf("\n%d\n", n);
        write(1, buf, n);
    }
    printf("%s\n", "end");
    return 0;
}
```

```c
#include <unistd.h>
#include <stdio.h>
int getchar1();

/****************************
 * 不带缓存的getchar1
 * 输入：qwer\n
 * 返回1：q
 * 返回2：w
 ****************************/
int main() {
    char c1 = getchar1();
    putchar(c1);
    char c2 = getchar();
    putchar(c2);
    return 0;
}

int getchar1() {
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}
```

```c
#include <unistd.h>
#include <stdio.h>
#define BUFSIZE 3
int getchar1();

/****************************
 * 带缓存的getchar1
 * 输入：qwer\n
 * 返回1：q
 * 返回2：r
 ****************************/
int main() {
    char c1 = getchar1();
    putchar(c1);
    char c2 = getchar();
    putchar(c2);
    return 0;
}

int getchar1() {
    static char buf[BUFSIZE];
    static char *bufp = buf;
    static int n = 0;
    
    if (n == 0) {
        n = read(0, buf, sizeof(buf));
        bufp = buf;
    }
    
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
```

## extern，include

- extern：表示变量是全局的
- include：用于导入变量

```c
/*Demo.h*/ 
#ifndef _DEMO_H_  
#define _DEMO_H_  
  
extern int a;  
extern int b;  
int add(int a, int b);  
  
#endif
```

```c
/*Demo.c*/  
#include "Demo.h"   
int a = 10;  
int b = 20;  
  
int add(int l, int r) {  
    return l + r;  
}
```

```c
#include "Demo.h"  
#include <stdio.h>
  
int main() {
    printf("%d, %d, %d", a, b, add(a, b));
    return 0;
}  
```

## NULL

```c
#include <stdio.h>

int main() {
    printf("%d", NULL == 0);          // 1
    printf("%d", NULL == (char *) 0); // 1
    printf("%s", 0);                  // (null)
    printf("%s", (char *) 0);         // (null)
    return 0;
}
```

## _flushbuf

```c
int _flushbuf(int x, FILE *fp) {
    
    if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE)         /* 检查文件状态 */
        return EOF;
        
    int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;       /* 设置文件缓存空间 */
    if (fp->base == NULL)                                  /* 没有缓存，可能是因为没有初始化 */
        if (fp->base = (char *) malloc(bufsize) == null)
            return EOF;
    
    write(fp->fd, fp->base, bufsize);                      /* flush */
    
    fp->ptr = fp->base;                                    /* 重置 */
    fp->cnt = 0;
    
    *fp->ptr++ = x;                                        /* 更新 */
    fp->cnt++;
    
    return x;
}
```

## 对齐

- [失传的C结构体打包技艺](https://github.com/ludx/The-Lost-Art-of-C-Structure-Packing)
- [C语言的struct/union字节对齐详解](http://blog.csdn.net/keyearth/article/details/6129882)