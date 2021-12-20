# string

## 初始化

```cpp
#include <iostream>
#include <string>


int main() {
    std::string a1;
    std::cout << a1 << std::endl;

    std::string a2("a2");
    std::cout << a2 << std::endl;

    auto a3("a3");
    std::cout << a3 << std::endl;

    std::string a4 = "a4";
    std::cout << a4 << std::endl;

    auto a5 = "a5";
    std::cout << a5 << std::endl;

    std::string a6 = std::string("a6");
    std::cout << a6 << std::endl;

    auto a7 = std::string("a7");
    std::cout << a7 << std::endl;

    return 0;
}
```
