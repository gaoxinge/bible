## 第10章 内存

### stack

#### 代码

```c
int swap_add(int *xp, int *yp) {
    int x = *xp;
    int y = *yp;
    
    *xp = y;
    *yp = x;
    return x + y;
}

int caller() {
    int arg1 = 534;
    int arg2 = 1057;
    int sum = swap_add(&arg1, &arg2);
    int diff = arg1 - arg2;
    
    return sum * diff;
}
```

#### 汇编

```
swap_add:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx

	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	(%edx), %ebx
	movl	(%ecx), %eax
	movl	%eax, (%edx)
	movl	%ebx, (%ecx)
	addl	%edx, %eax

	popl	%ebx
	popl	%ebp
	ret

caller:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$534, -4(%ebp)
	movl	$1057, -8(%ebp)

	leal	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)

	call	swap_add

	movl	-4(%ebp), %edx
	subl	-8(%ebp), %edx
	imull	%edx, %eax
	leave
	ret
```

#### 调用

```
-----------
| old %ebp| <- %ebp
-----------
| arg1    |
-----------
| arg2    | <- %esp
-----------
```

```
-----------
| old %ebp| <- %ebp
-----------
| arg1    |
-----------
| arg2    |
-----------
| &arg2   |
-----------
| &arg1   | <- %esp
-----------
```

```
-----------
| old %ebp|
-----------
| arg1    |
-----------
| arg2    |
-----------
| &arg2   |
-----------
| &arg1   |
-----------
| return  |
-----------
| old %ebp| <- %ebp
-----------
| old %ebx| <- %esp
-----------
```

```
-----------
| old %ebp|
-----------
| arg1    |
-----------
| arg2    |
-----------
| &arg2   |
-----------
| &arg1   |
-----------
| return  |
-----------
| old %ebp| <- %ebp
-----------
| old %ebx| <- %esp
-----------
```

```
-----------
| old %ebp| <- %ebp
-----------
| arg1    |
-----------
| arg2    |
-----------
| &arg2   |
-----------
| &arg1   | <- %esp
-----------
```

#### 其他

- `%eax`用于存放返回值

### 参考

- [7. Memory : Stack vs Heap](https://www.gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html)\
- [What and where are the stack and heap?](https://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap)
- [Where are multiple stacks and heaps put in virtual memory?](https://stackoverflow.com/questions/16155690/where-are-multiple-stacks-and-heaps-put-in-virtual-memory)
- [Does Python have a stack/heap and how is memory managed?](https://stackoverflow.com/questions/14546178/does-python-have-a-stack-heap-and-how-is-memory-managed)
- [What is the stack in Python?](https://stackoverflow.com/questions/25457358/what-is-the-stack-in-python)