- [google/googletest](https://github.com/google/googletest)
- [google/googletest/googletest](https://github.com/google/googletest/tree/main/googletest)
- [cmake](https://google.github.io/googletest/quickstart-cmake.html)
- [primer](https://google.github.io/googletest/primer.html)
- [example](https://google.github.io/googletest/)
- [template 1](https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html)
- [template 2](https://github.com/kaizouman/gtest-cmake-example)

```
$ cd external
$ git clone git@github.com:google/googletest.git --depth=1 

$ cmake -B build/ -Dgtest_force_shared_crt=ON
$ cmake --build build/
$ ctest --test-dir build/ -C DEBUG -VV
```
