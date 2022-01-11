- [opencv/opencv](https://github.com/opencv/opencv)
- [Using OpenCV with gcc and CMake](https://docs.opencv.org/4.x/db/df5/tutorial_linux_gcc_cmake.html)
- [Installation in Windows](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html)
- [Linking problem with OpenCV and CMake](https://stackoverflow.com/questions/7417242/linking-problem-with-opencv-and-cmake)

```
$ cd external
$ git clone git@github.com:opencv/opencv.git --depth=1

$ cmake -B build/
$ cmake --build build/ --config Release
$ ./build/bin/Release/main.exe lena.png
```
