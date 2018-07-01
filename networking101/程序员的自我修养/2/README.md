## 第2章 编译和链接

### 整体流程

```
            cpp                     ccl                  as               ld
hello.c -------------> hello.i -----------> hello.s ----------> hello.o ---------> hello.out
```

### 预编译

```
$ gcc -E hello.c -o  hello.i
$ cpp ...
```

### 编译

```
$ gcc -S hello.i -o hello.s
$ gcc -S hello.c -o hello.s
$ ccl ...
```

### 汇编

```
$ gcc -c hello.s -o hello.o
$ gcc -c hello.c -o hello.o
$ as ...
```

### 静态链接

```
$ gcc -static hello.o -o hello.out
$ gcc -static hello.c -o hello.out
$ ld  -static ...
```

### 动态链接

```
$ gcc hello.o -o hello.out
$ gcc hello.c -o hello.out
$ ld  ...
```