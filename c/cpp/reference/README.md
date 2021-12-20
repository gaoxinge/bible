# 引用

## const

```cpp
#include <iostream>

int main() {
    int a = 0;
    int &b = a;

    std::cout << a << " " << b << std::endl;  // 0
    a = 1;
    std::cout << a << " " << b << std::endl;  // 1
    b = 2;
    std::cout << a << " " << b << std::endl;  // 2

    return 0;
}
```

```cpp
#include <iostream>

int main() {
    int a = 0;
    const int &b = a;

    std::cout << a << " " << b << std::endl;  // 0
    a = 1;
    std::cout << a << " " << b << std::endl;  // 1

    return 0;
}
```

```cpp
#include <iostream>

int main() {
    const int a = 0;
    const int &b = a;

    std::cout << a << " " << b << std::endl;  // 0

    return 0;
}
```
