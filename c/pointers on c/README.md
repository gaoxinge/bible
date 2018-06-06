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

## 字符数组的初始化

```c
#include <stdio.h>

int main() {
    char  message1[] = {'H', 'e', 'l', 'l', 'o', '\0'};  // 字符数组
    char  message2[] = "Hello";                          // 字符数组
    char* message3   = "Hello";                          // 字符串常量
    
    printf("%s %s %s", message1, message2, message3);
    
    return 0;
}
```

## 一维数组

- `a[10]`: 10, 行
- `a[1]` 或者 `*(a + 1)`
- `int f(int *a)` 或者 `int f(int a[])`

```c
#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *p  = a;
    
    for (int i = 0; i < 10; ++i)
        printf("%d ", a[i]);
    
    for (; p < a + 10; ++p)
        printf("%d ", *p);
    
    return 0;
}
```

```c
#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *p  = a;
    printf("%p\n", a);
    printf("%p\n", p);
    return 0;
}
```

## 二维数组

- `a[2][10]`: 2-10, 行列
- `a[1][1]` 或者 `*(a[1] + 1)` 或者 `*(*(a + 1) + 1)`
- `int f(int (*a)[10])` 或者 `int f(int a[][10])`

```c
#include <stdio.h>

int main() {
    int a[2][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 10; ++j)
            printf("%d ", a[i][j]);
    printf("\n");
    
    int (*p1)[10]  = a; // &a[0]
    for (; p1 < a + 2; ++p1)
        for (int j = 0; j < 10; ++j)
            printf("%d ", *(*p1 + j));
    printf("\n");
    
    int *p2 = (int*) a; // a[0], &a[0][0]
    for (; p2 < a[0] + 20; ++p2)
        printf("%d ", *p2);
    printf("\n");
    
    return 0;
}
```

```c
#include <stdio.h>

int main() {
    int a[2][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    printf("%p\n", a);
    printf("%p\n", a[0]);
    
    int (*p1)[10]  = a; // &a[0]
    printf("%p\n", p1);
    printf("%p\n", *p1);
    
    int *p2 = (int*) a; // a[0], &a[0][0]
    printf("%p\n", p2);
    
    return 0;
}
```

## 一维数组与二维数组

```c
#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *p  = a;
    int (*p1)[1] = (int (*)[1]) a;
    int (*p2)[2] = (int (*)[2]) a;
    int (*p3)[3] = (int (*)[3]) a;
    
    for (int i = 0; i < 10; ++i)
        printf("%d ", a[i]);
    printf("\n");
    
    for (; p < a + 10; ++p)
        printf("%d ", *p);
    printf("\n");
    
    for (; p1 < (int (*)[1])(a + 10); ++p1)
        printf("%d ", **p1);
    printf("\n");
    
    for (; p2 < (int (*)[2])(a + 10); ++p2)
        printf("%d ", **p2);
    printf("\n");
    
    for (; p3 < (int (*)[3])(a + 10); ++p3)
        printf("%d ", **p3);
    printf("\n");
    
    return 0;
}
```