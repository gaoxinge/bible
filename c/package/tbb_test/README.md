- [oneapi-src/oneTBB](https://github.com/oneapi-src/oneTBB)
- [oneapi-src/oneTBB/examples](https://github.com/oneapi-src/oneTBB/tree/master/examples)
- [oneapi-src/oneAPI-samples/Libraries/oneTBB](https://github.com/oneapi-src/oneAPI-samples/tree/master/Libraries/oneTBB)
- [yuki-koyama/hello-tbb-cmake](https://github.com/yuki-koyama/hello-tbb-cmake)
- [Part 2: tbb::parallel_for](https://chryswoods.com/parallel_c%2b%2b/parallel_for.html)

```
$ cmake -B build -DTBB_TEST=OFF -DBUILD_SHARED_LIBS=OFF
$ cmake --build build/
$ ./build/Debug/main.exe
1839.34
```
