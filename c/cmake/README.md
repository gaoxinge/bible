# cmake

## command

```
$ cmake -B build/
$ cmake --build build/
$ cmake --install build/
$ ./build/Debug/main.exe
Hello, world!
```

```
$ cmake -B build/
$ cmake --build build/ --config Release
$ cmake --install build/ --prefix install/
$ ./install/bin/main.exe
Hello, world!
```

```
$ cmake -B build/ -DCMAKE_INSTALL_PREFIX=install
$ cmake --build build/ --config Release
$ cmake --install build/
$ ./install/bin/main.exe
Hello, world!
```

```
$ cmake -B build/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=install
$ cmake --build build/ --config Release
$ cmake --install build/
$ ./install/bin/main.exe
Hello, world!
```
