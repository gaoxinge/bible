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