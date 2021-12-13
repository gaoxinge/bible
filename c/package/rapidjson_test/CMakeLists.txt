cmake_minimum_required(VERSION 3.10)
project(rapidjson_test)

add_executable(main main.cpp)
target_include_directories(main PUBLIC external/rapidjson/include)
