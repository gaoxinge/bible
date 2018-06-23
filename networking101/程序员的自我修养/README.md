## 第6章 可执行文件的装载和进程

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
