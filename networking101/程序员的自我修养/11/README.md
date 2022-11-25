## 第11章 运行库

### 入口函数

```c
#include <stdio.h>

void main() {
	printf("Hello World!\n");
}
```

```c
#include <stdio.h>
#include <stdlib.h>

void test() {
	printf("Hello World!\n");
	exit(0);
}
```

```
$ gcc main.c -e test -nostartfiles
```

```c
#include <stdio.h>
#include <stdlib.h>

void _start() {
	printf("Hello World!\n");
	exit(0);
}
```

```
$ gcc main.c -nostartfiles
```

### 汇编

- 汇编文件
- 内联汇编
  - 宏
  - asm函数

### 系统调用

- `unistd.h`
- `sys/syscall.h`
- 汇编
  
### 参考

- [不以main为入口的函数](http://www.cnblogs.com/tianzeng/p/9248548.html)