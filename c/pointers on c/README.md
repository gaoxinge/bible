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

## 指针数组

```c
#include <string.h>
#include <stdio.h>

const char* keyword[] = {
    "do",
    "for",
    "if",
    "register",
    "return",
    "switch",
    "while"
};

#define N_KEYWORD (sizeof(keyword) / sizeof(keyword[0]))
int lookup_keyword(const char* desired_word, const char* keyword_table[], const int size);


int main() {
    printf("%d\n", sizeof(keyword));      // 28 = sizeof(char*) * 7
    printf("%d\n", sizeof(keyword[0]));   // 4  = sizeof(char*)
    printf("%d\n", lookup_keyword("a",        keyword, N_KEYWORD));
    printf("%d\n", lookup_keyword("for",      keyword, N_KEYWORD));
    printf("%d\n", lookup_keyword("register", keyword, N_KEYWORD));
    
    return 0;
}

int lookup_keyword(const char* const desired_word, 
                   const char* keyword_table[], 
                   const int size) {
    const char** kwp;
    
    for (kwp = keyword_table; kwp < keyword_table + size; kwp++)
        if (strcmp(desired_word, *kwp) == 0)
            return kwp - keyword_table;
        
    return -1;
}
```

```c
#include <string.h>
#include <stdio.h>

const char keyword[][9] = {
    "do",
    "for",
    "if",
    "register",
    "return",
    "switch",
    "while"
};

#define N_KEYWORD (sizeof(keyword) / sizeof(keyword[0]))
int lookup_keyword(const char* desired_word, const char keyword_table[][9], const int size);


int main() {
    printf("%d\n", sizeof(keyword));      // 63 = 9 * sizeof(char) * 7
    printf("%d\n", sizeof(keyword[0]));   // 9  = 9 * sizeof(char)
    printf("%d\n", lookup_keyword("a",        keyword, N_KEYWORD));
    printf("%d\n", lookup_keyword("for",      keyword, N_KEYWORD));
    printf("%d\n", lookup_keyword("register", keyword, N_KEYWORD));
    
    return 0;
}

int lookup_keyword(const char* const desired_word, 
                   const char keyword_table[][9], 
                   const int size) {
    const char (*kwp)[9];
    
    for (kwp = keyword_table; kwp < keyword_table + size; kwp++)
        if (strcmp(desired_word, *kwp) == 0)
            return kwp - keyword_table;
        
    return -1;
}
```

## 双链表

```c
if (next != null) {
    if (this != rootp) {
        newnode->fwd = next;
        this->fwd = newnode;
        newnode->bwd = this;
        next->bwd = newnode;
    } else {
        newnode->fwd = next;
        rootp->fwd = newnode;
        newnode->bwd = NULL;
        next->bwd = newnode;
    }
} else {
    if (this != rootp) {
        newnode->fwd = NULL;
        this->fwd = newnode;
        newnode->bwd = this;
        rootp->bwd = newnode;
    } else {
        newnode->fwd = NULL;
        rootp->fwd = newnode;
        newnode->bwd = NULL;
        rootp->bwd = newnode;
    }
}
```

```c
if (next != null) {
    newnode->fwd = next;
    if (this != rootp) {
        this->fwd = newnode;
        newnode->bwd = this;
    } else {
        rootp->fwd = newnode;
        newnode->bwd = NULL;
    }
    next->bwd = newnode;
} else {
    newnode->fwd = NULL;
    if (this != rootp) {
        this->fwd = newnode;
        newnode->bwd = this;
    } else {
        rootp->fwd = newnode;
        newnode->bwd = NULL;
    }
    rootp->bwd = newnode;
}
```

```c
if (this != rootp) {
    this->fwd = newnode;
    newnode->bwd = this;
} else {
    rootp->fwd = newnode;
    newnode->bwd = NULL;
}

if (next != null) {
    newnode->fwd = next;
    next->bwd = newnode;
} else {
    newnode->fwd = NULL;
    rootp->bwd = newnode;
}
```

```c
newnode->fwd = next;
this->fwd = newnode;

if (this != rootp) {
    newnode->bwd = this;
} else {
    newnode->bwd = NULL;
}

if (next != null) {
    next->bwd = newnode;
} else {
    rootp->bwd = newnode;
}
```

## 堆栈

- [数组堆栈](https://github.com/gaoxinge/bible/tree/master/c/pointers%20on%20c/%E6%95%B0%E7%BB%84%E5%A0%86%E6%A0%88)
- [动态数组堆栈](https://github.com/gaoxinge/bible/tree/master/c/pointers%20on%20c/%E5%8A%A8%E6%80%81%E6%95%B0%E5%A0%86%E6%A0%88)
- [用动态数组实现堆栈](https://github.com/gaoxinge/bible/tree/master/c/pointers%20on%20c/%E7%94%A8%E5%8A%A8%E6%80%81%E6%95%B0%E7%BB%84%E5%AE%9E%E7%8E%B0%E5%A0%86%E6%A0%88)