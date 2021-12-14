cmake_minimum_required(VERSION 3.10)
project(backward_cpp_test)

add_subdirectory(external/backward-cpp)
add_executable(main main.cpp)
add_backward(main)
