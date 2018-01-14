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