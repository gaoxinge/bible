cmake_minimum_required(VERSION 3.10)
project(range_v3_test)
set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
target_include_directories(main PUBLIC external/range-v3/include)
