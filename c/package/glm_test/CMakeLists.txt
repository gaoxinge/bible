cmake_minimum_required(VERSION 3.10)
project(glm_test)

add_executable(main main.cpp)
target_include_directories(main PUBLIC external/glm)
