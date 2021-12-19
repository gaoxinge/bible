# 类型转化

## 内置类型

```cpp
#include <iostream>

int main() {
    // implicit cast, promotion
    int a1 = 1;
    double a2 = a1;
    std::cout << a1 << " " << a2 << std::endl;

    // implicit cast, warning
    double b1 = 1;
    int b2 = b1;
    std::cout << b1 << " " << b2 << std::endl;

    // explicit cast, old style
    double c1 = 1;
    int c2 = (int) c1;
    std::cout << c1 << " " << c2 << std::endl;

    // explicit cast
    double d1 = 1;
    int d2 = static_cast<int>(d1);
    std::cout << d1 << " " << d2 << std::endl;

    return 0;
}
```

## 指针类型

```cpp
#include <iostream>

int main() {
    // implicit cast, promotion
    int *a1;
    void *a2 = a1;
    std::cout << a1 << " " << a2 << std::endl;

    // implicit cast, error
    /*
    void *b1;
    int *b2 = b1;
    std::cout << b1 << " " << b2 << std::endl;
    */

    // explicit cast, old style
    void *c1;
    int *c2 = (int *) c1;
    std::cout << c1 << " " << c2 << std::endl;

    // explicit cast
    void *d1;
    int *d2 = static_cast<int *>(d1);
    std::cout << d1 << " " << d2 << std::endl;

    return 0;
}
```

```cpp
#include <iostream>

int main() {
    // different type, error
    /*
    int *a1;
    double *a2 = a1;
    std::cout << a1 << " " << a2 << std::endl;
    */

    // explicit cast, old style
    int *b1;
    double *b2 = (double *) b1;
    std::cout << b1 << " " << b2 << std::endl;

    // explicit cast
    int *c1;
    double *c2 = reinterpret_cast<double *>(c1);
    std::cout << c1 << " " << c2 << std::endl;

    return 0;
}
```
