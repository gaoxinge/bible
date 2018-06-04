## sizeof

```c
#include <stdio.h>

int main() {
    int x = 0;
    int y = 0;
    printf("%d\n", sizeof(int));        // 4
    printf("%d\n", sizeof x);           // 4
    printf("%d\n", sizeof(x));          // 4
    printf("%d\n", sizeof(x = y + 1));  // 4
    printf("%d\n", x);                  // 0
    printf("%d\n", x = y + 1);          // 1
    printf("%d\n", x);                  // 1
    return 0;
}
```

## 指针的效率

```c
#define SIZE 50

int x[SIZE];
int y[SIZE];

void try5() {
    register int *p1, *p2;
    for (p1 = x, p2 = y; p1 < &x[SIZE];)
        *p1++ = *p2++;
}
```

```
LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	$_x, %ebx
	movl	$_y, %esi
	jmp	L2
L3:
	movl	%ebx, %eax
	leal	4(%eax), %ebx
	movl	%esi, %edx
	leal	4(%edx), %esi
	movl	(%edx), %edx
	movl	%edx, (%eax)
L2:
	cmpl	$_x+200, %ebx
	jb	L3
	nop
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
```

```c
#define SIZE 50

int x[SIZE];
int y[SIZE];

void try6() {
    register int *p1, *p2;
    for (p1 = x, p2 = y; p1 < x + SIZE;)
        *p1++ = *p2++;
}
```

```
LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	$_x, %ebx
	movl	$_y, %esi
	jmp	L2
L3:
	movl	%ebx, %eax
	leal	4(%eax), %ebx
	movl	%esi, %edx
	leal	4(%edx), %esi
	movl	(%edx), %edx
	movl	%edx, (%eax)
L2:
	movl	$_x+200, %eax
	cmpl	%eax, %ebx
	jb	L3
	nop
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
```

## 作为函数参数的数组名

```c
void strcpy(char* buffer, char const* string) {
    while((*buffer++ = *string++) != '\0')
        ;
}
```

- `const char*` 和 `char const*` 为指向常量的指针
- `char* const` 为指针常量
- `++` 的优先级高于 `*`
- strcpy中的buffer需要提前分配内存 