cmake_minimum_required(VERSION 3.10)
project(magic_enum_test)
set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
target_include_directories(main PUBLIC external/magic_enum/include)
