## 第7章 动态链接

### 7.3 地址无关代码

#### 命令

- `-shared`：共享对象
- `-fpic`，`-fPIC`：position independent code
- `-fpie`，`-fPIE`：position independent executable

#### 指令

- [指令存储在外存中还是内存？](https://www.zhihu.com/question/57522333)
- [程序的机器级表示<CSAPP>](https://blog.csdn.net/qq_20183489/article/details/53856926)
- [csapp chapter3:程序的机器级表示](http://ju.outofmemory.cn/entry/107328)

##### 观察1

|类型|格式|地址|值|
|----|----|----|--|
|立即数|$Imm|-|Imm|
|存储器|Imm|M[Imm]|V(M[Imm])|
|寄存器|E_e|E_e|V(E_e)|
|存储器|(E_e)|M[V(E_e)]|V(M[V(E_e)])|

|指令|S|D|
|----|-|-|
|mov|值|地址|
|add|值|地址|

##### 观察2

```c
int sum1(int a, int b) {
    return a + b;
}

int sum2(int a, int b, int c) {
    return a + b + c;
}

int sum(int *a, int b) {
    return *a + b;
}
```

```
a.o:     file format pe-i386


Disassembly of section .text:

00000000 <_sum1>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	8b 55 08             	mov    0x8(%ebp),%edx    // a = M[V(%ebp) + 8]
   6:	8b 45 0c             	mov    0xc(%ebp),%eax    // b = M[V(%ebp) + 12]
   9:	01 d0                	add    %edx,%eax
   b:	5d                   	pop    %ebp
   c:	c3                   	ret    

0000000d <_sum2>:
   d:	55                   	push   %ebp
   e:	89 e5                	mov    %esp,%ebp
  10:	8b 55 08             	mov    0x8(%ebp),%edx    // a = M[V(%ebp) + 8]
  13:	8b 45 0c             	mov    0xc(%ebp),%eax    // b = M[V(%ebp) + 12]
  16:	01 c2                	add    %eax,%edx
  18:	8b 45 10             	mov    0x10(%ebp),%eax   // c = M[V(%ebp) + 16]
  1b:	01 d0                	add    %edx,%eax
  1d:	5d                   	pop    %ebp
  1e:	c3                   	ret    

0000001f <_sum>:
  1f:	55                   	push   %ebp
  20:	89 e5                	mov    %esp,%ebp
  22:	8b 45 08             	mov    0x8(%ebp),%eax
  25:	8b 10                	mov    (%eax),%edx
  27:	8b 45 0c             	mov    0xc(%ebp),%eax
  2a:	01 d0                	add    %edx,%eax
  2c:	5d                   	pop    %ebp
  2d:	c3                   	ret    
  2e:	90                   	nop
  2f:	90                   	nop
```

##### 观察3

- 函数的参数：0x8(%ebp)
- 函数的局部变量：%eax或者0x8(%ebp)
- `-shared -fPIC`的static：0x28(%ecx)
- `-shared -fPIC`的extern：mov 0xfffffff8(%ecx) %eax; (%eax)
- 指针：mov 0x8(%ebp) %eax; (%eax)

##### 观察4

- 汇编：汇编可以把地址存放在内存上，通过指针可以弥补c和汇编的这个鸿沟
- 其他语言：指针vs引用

#### 例子

```c
// pic.c
static int a;
extern int b;
extern void ext();

void bar() {
    a = 1;
    b = 2;
}

void foo() {
    bar();
    ext();
}
```

```c
// global.c
int b = 1;
void ext() {};
```

```
$ gcc -shared -fPIC -o pic.so pic.c global.c
```

#### 类型1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

- `-c`：相对跳转和调用
- `-shared -fPIC`：相对跳转和调用

#### 类型2

- `-c`：相对地址访问
- `-shared -fPIC`：相对地址访问

#### 类型3

- `-shared -fPIC`：GOT

#### 类型4

#### 共享模块的全局变量问题

- 当module.c为
- 当module.c

#### 数据段地址无关性

#### 延迟绑定（PLT）