# libuv

## gyp

- [GYP](https://gyp.gsrc.io/index.md)
- [bnoordhuis/gyp](https://github.com/bnoordhuis/gyp)

## windows 

### MSVC静态库

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

### MSYS2

- install
  - [MSYS2 installer](http://www.msys2.org/)
  - [How to install MinGW-w64 and MSYS2?](https://stackoverflow.com/questions/30069830/how-to-install-mingw-w64-and-msys2)
  - [MSYS2 - Install gcc or toolchain?](https://stackoverflow.com/questions/51724007/msys2-install-gcc-or-toolchain)
- package
  - [msys2/MINGW-packages](https://github.com/msys2/MINGW-packages)
- server
  - [Win7下搭建Msys2x64编译环境](http://blog.illidan.org/2016/11/10/Msys2/)
  - [repo.msys2.org very slow or unreachable](https://github.com/msys2/MSYS2-packages/issues/1098)
  
### build from source

```
> sh autogen.sh
> ./configure
> make
> make check
> make install
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    return 0;
}
```

```
> gcc -o main -I include main.c .libs/libuv.a -ladvapi32 -liphlpapi -lpsapi -luser32 -luserenv -lws2_32
> ./main
Now quitting.
```

- [issue982](https://github.com/libuv/libuv/issues/982)
  - use autotools instead of GYP
  - use MSYS2 to install gcc, mingw-w64-x86_64-toolchain, base-devel firstly
- [issue820](https://github.com/libuv/libuv/issues/820)
  - both -DWIN32_LEAN_AND_MEAN and Makefile.mingw have been add in Makefile
- [issue1194](https://github.com/libuv/libuv/issues/1194) & [issue](https://github.com/libuv/libuv/issues/1200)
  - fix in mingw32, however there may be still bugs in mingw64
- [libuv之mingw64环境搭建及编译Libuv](https://blog.csdn.net/linuxandroidwince/article/details/72312708)
  - compile with -ladvapi32 -liphlpapi -lpsapi -luser32 -luserenv -lws2_32
