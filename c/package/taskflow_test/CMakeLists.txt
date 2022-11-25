cmake_minimum_required(VERSION 3.10)
project(taskflow_test)
set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
target_include_directories(main PUBLIC external/taskflow)

add_executable(main1 main1.cpp)
target_include_directories(main1 PUBLIC external/taskflow)

add_executable(main2 main2.cpp)
target_include_directories(main2 PUBLIC external/taskflow)

add_executable(main3 main3.cpp)
target_include_directories(main3 PUBLIC external/taskflow)
