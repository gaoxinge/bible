- [google/glog](https://github.com/google/glog)

```
$ cd external
$ git clone git@github.com:google/glog.git --depth=1

$ cmake -B build/ -DBUILD_SHARED_LIBS=OFF
$ cmake --build build/
$ ./build/Debug/main.exe
WARNING: Logging before InitGoogleLogging() is written to STDERR
I20211215 00:55:55.519480  9740 main.cpp:4] Hello, world!
```
