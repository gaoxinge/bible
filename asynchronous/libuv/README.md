# libuv

## gyp

- [GYP](https://gyp.gsrc.io/index.md)
- [bnoordhuis/gyp](https://github.com/bnoordhuis/gyp)

## windows 

### 静态库

```c
// hello.c
#include <stdio.h>

void hello() {
    puts("Hello World");
}
```

```c
// main.c
extern void hello();

int main() {
    hello();
    return 0;
}
```


```
> cl /c hello.c
> lib /OUT:hello.lib hello.obj
> cl main.c hello.lib
> main
Hello World
```