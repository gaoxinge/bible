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