## 第6章 可执行文件的装载和进程

### 6.1 进程虚拟地址空间

- 程序（可执行文件）：静态概念
- 进程：动态概念
- 32位：硬件，操作系统，c（指针4字节），寻址范围（0 - 2**32-1）
- 64位：硬件，操作系统，c（指针8字节），寻址范围（0 - 2**64-1）
- linux：1GB（操作系统），3GB（用户进程）
- windows：2GB（操作系统），2GB（用户进程）
- pae，ame，xms，mmap

### 6.2 页映射

- [Memory management unit](https://en.wikipedia.org/wiki/Memory_management_unit)
- [硬件篇之MMU](https://blog.csdn.net/ipmux/article/details/19167605)
- [c语言中的虚拟地址](https://blog.csdn.net/bingyu_1/article/details/80224159)
- FIFO，LUR
- 页错误

### 6.3 从操作系统角度看可执行文件的装载

- 创建一个独立的虚拟地址空间：建立虚拟地址和物理地址的页映射
- 读取可执行文件头，并建立虚拟空间与可执行文件的映射关系：建立可执行文件和虚拟地址空间的映射
- 将CPU的指令寄存器设置成可执行文件的入口，启动运行：入口在ELF Header中
- 执行过程中，通过页错误的方式，先把指令和数据从可执行文件加载到虚拟地址空间，再从虚拟地址加载到物理地址，最后执行

### 6.4 进程虚存空间分布

#### 6.4.1 ELF文件链接视图和执行视图

- linux：虚拟内存区域VMA，virtual memory area；windows：虚拟段virtual section
- section：elf的链接视图；segment：elf的执行视图（VMA）（program header table）（可执行文件，共享目标文件）
- 参见P164图6-8

```c
#include <stdlib.h>

int main() {
	while (1) {
		sleep(1000);
	}
	return 0;
}
```

```
$ gcc -static SectionMapping.c -o SectinMapping.elf
$ readelf -S SectionMapping.elf
$ readelf -l SectionMapping.elf 
```

#### 6.4.2 堆和栈

- 参见P167图6-9

```
$ ./SectionMapping.elf &
$ cat /proc/21963/maps
```

#### 6.4.3 堆的最大申请数量

```c
#include <stdio.h>
#include <stdlib.h>

unsinged maximum = 0;

int main() {
	unsigned blocksize[] = {1024 * 1024, 1024, 1};
	int i, count;
	for (i = 0; i < 3; i++) {
		for (count = 1; ; count++) {
			void *block = malloc(maximum + blocksize[i] * count);
			if (block) {
				maximum = maximum + blocksize[i] * count;
				free(block);
			} else {
				break;
			}
		}
	}
	printf("maximum malloc size = %u bytes\n", maximum);
}
```

- linux：4GB进程，3GB用户空间，2.9GB堆内存
- windows：4GB进程，2GB用户空间，1.5GB堆内存

#### 6.4.4 段地址对齐

- 略

#### 6.4.5 进程栈初始化

- 栈内存
  - 环境变量
  - 命令行参数
  - main，argc，argv

### 6.5 Linux内核装载ELF过程简介

#### 魔数

- 魔数
  - 代码里面的常数
  - 文件里面的常数
- 魔数（文件）：用于程序区别过滤
  - 魔数
  - 后缀
- 常见文件
  - ELF：0x7F，'e'，'l'，'f'
  - Java class：'c'，'a'， 'f'，'e'
  - shell, perl, python：'#'，'!'
- 参考
  - [Magic number (programming)](https://en.wikipedia.org/wiki/Magic_number_(programming))
  - [magic number 详解](https://blog.csdn.net/universe_hao/article/details/52779699)
  - [编程中的「魔数」（magic number）是什么意思？平时我们能接触到哪些魔数？](https://www.zhihu.com/question/22018894)
  - [为什么算法中会出现magic number?](https://www.zhihu.com/question/29395261)

#### 文件

- 方法
  - open
  - read
  - write
  - close
- 操作
  - 双击，右击：不可靠
  - 命令行：可靠
- 命令行
  - 主进程fork子进程，主进程wait
  - 子进程调用execve执行elf文件，调用sys_execve：进入内核态，进行一些参数的检查复制
  - sys_execve调用do_execve：检查魔数
  - do_execve调用search_binary_handle：匹配魔数
    - elf：do_execve调用load_elf_binary
    - out：do_execve调用load_aout_binary
    - 脚本：do_execve调用load_script
  - do_execve调用load_elf_binary
    - 装载：参见 (1) - (5)
  - 返回do_execve
  - 返回sys_execve：进入用户态
  - 装载完成，程序开始执行
  - 程序执行结束，子进程结束，父进程唤醒
- 参考
  - [文本文件和二进制文件的区别？请举例说明](https://www.zhihu.com/question/19971994)
  - [详解二进制文件和文本文件的区别暨换行和回车详解](https://blog.csdn.net/wu_nan_nan/article/details/53469958)
  - [文件读写](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431917715991ef1ebc19d15a4afdace1169a464eecc2000)

#### 补充

```python
# -*- coding: utf-8 -*-

f = open("1/test.jpg", "rb")
result = f.read()
print "%#x" % ord(result[0]), "%#x" % ord(result[1])
f.close()

f = open("1/test.class", "rb")
result = f.read()
print "%#x" % ord(result[0]), "%#x" % ord(result[1]), "%#x" % ord(result[2]), "%#x" % ord(result[3])
f.close()

f = open("1/test.exe", "rb")
result = f.read()
print "%#x" % ord(result[0]), "%#x" % ord(result[1])
f.close()
``` 
