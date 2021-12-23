# 函数

## pointer to function

### 申明和定义

```cpp
#include <iostream>

typedef int INT;

// typedef int (*)(int, int) F;
typedef int(*F)(int, int);

int f(int a, int b) {
    return a + b;
}

int main() {
    int a1 = 0;
    INT a2 = 0;
    std::cout << a1 << " " << a2 << std::endl;

    int (*f1)(int, int) = f;
    F f2 = f;
    std::cout << f1 << " " << f2 << std::endl;

    return 0;
}
```

### 调用

```cpp
#include <iostream>

typedef int(*F)(int, int);

int f(int a, int b) {
    return a + b;
}

int main() {
    std::cout << f << std::endl;
    std::cout << &f << std::endl;
    std::cout << *f << std::endl;
    std::cout << f(1, 2) << std::endl;
    std::cout << (&f)(1, 2) << std::endl;
    std::cout << (*f)(1, 2) << std::endl;

    F f0 = f;
    std::cout << f0 << std::endl;
    std::cout << &f0 << std::endl; // pointer to pointer
    std::cout << *f0 << std::endl;
    std::cout << f0(1, 2) << std::endl;
    // std::cout << (&f0)(1, 2) << std::endl;
    std::cout << (*f0)(1, 2) << std::endl;

    return 0;
}
```
