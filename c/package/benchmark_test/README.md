- [google/benchmark](https://github.com/google/benchmark)

```
$ cd external
$ git clone git@github.com:google/benchmark.git --depth=1

$ cmake -B build/ -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
$ cmake --build build/
$ ctest --test-dir build/ -C DEBUG -VV
$ ./build/Debug/bench
$ ./build/Debug/main
```
