# 指针

## unique_ptr

### 传参

```cpp
#include <iostream>
#include <memory>

void test(std::unique_ptr<int> p) {
    *p = 10;
}

int main() {
    std::unique_ptr<int> up(new int(42));
    test(up);  // compiler error: can not copy
    std::cout << "up is nullptr: " << (up == nullptr) << std::endl;
    std::cout << "up is nullptr: " << (up.get() == nullptr) << std::endl;
    std::cout << *up << std::endl;
    return 0;
}
```

```cpp
#include <iostream>
#include <memory>

void test(std::unique_ptr<int> p) {
    *p = 10;
}

int main() {
    std::unique_ptr<int> up(new int(42));
    test(std::move(up));
    std::cout << "up is nullptr: " << (up == nullptr) << std::endl;  // true
    std::cout << "up is nullptr: " << (up.get() == nullptr) << std::endl;  // true
    std::cout << *up << std::endl;  // segmentation fault
    return 0;
}
```

```cpp
#include <iostream>
#include <memory>

void test(std::unique_ptr<int> &p) {
    *p = 10;
}

int main() {
    std::unique_ptr<int> up(new int(42));
    test(std::move(up));
    std::cout << "up is nullptr: " << (up == nullptr) << std::endl;  // false
    std::cout << "up is nullptr: " << (up.get() == nullptr) << std::endl;  // false
    std::cout << *up << std::endl;  // 10
    return 0;
}
```

```cpp
#include <iostream>
#include <memory>

void test(std::unique_ptr<int> &p) {
    *p = 10;
}

int main() {
    std::unique_ptr<int> up(new int(42));
    test(std::move(up));  // compile error
    std::cout << "up is nullptr: " << (up == nullptr) << std::endl;
    std::cout << "up is nullptr: " << (up.get() == nullptr) << std::endl;
    std::cout << *up << std::endl;
    return 0;
}
```

```cpp
#include <iostream>
#include <memory>

void test(std::unique_ptr<int> &&p) {
    *p = 10;
}

int main() {
    std::unique_ptr<int> up(new int(42));
    test(up);  // compiler error
    std::cout << "up is nullptr: " << (up == nullptr) << std::endl;
    std::cout << "up is nullptr: " << (up.get() == nullptr) << std::endl;
    std::cout << *up << std::endl;
    return 0;
}
```

```cpp
#include <iostream>
#include <memory>

void test(std::unique_ptr<int> &&p) {
    *p = 10;
}

int main() {
    std::unique_ptr<int> up(new int(42));
    test(std::move(up));
    std::cout << "up is nullptr: " << (up == nullptr) << std::endl;  // false
    std::cout << "up is nullptr: " << (up.get() == nullptr) << std::endl;  // false
    std::cout << *up << std::endl;  // 10
    return 0;
}
```
