# 数组

## 申明, 赋值和初始化

```c
#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4};
    a = {5, 6, 7, 8};  // error: expected expression before '{' token 
    
    int *b = {1, 2, 3, 4};
    b = {5, 6, 7, 8};  // error: expected expression before '{' token

    char c[5] = "1234";
    c = "5678";  // error: assignment to expression with array type

    char *d = "1234";
    d = "5678";

    return 0;
}
```

## 指针数组和数组指针

```c
#include <stdio.h>

int main() {
    int a1 = 1;
    int a2 = 2;
    int a[2] = {a1, a2};
    int *a1_ptr = &a1;
    int *a2_ptr = &a2;

    // array of pointer / pointer array / 指针数组
    int *b1[] = {a1_ptr, a2_ptr};
    printf("========== array pointer ==========\n");
    printf("1: %d\n", *b1[0]);
    printf("2: %d\n", *b1[1]);
    printf("1: %d\n", **b1);
    printf("2: %d\n", **(b1 + 1));
    
    // pointer to array / array pointer / 数组指针
    printf("========== pointer array =========\n");
    int (*b2)[2] = &a;
    printf("1: %d\n", (*b2)[0]);
    printf("2: %d\n", (*b2)[1]);
    printf("1: %d\n", **b2);
    printf("2: %d\n", *(*b2 + 1));

    return 0;
}
```
