cmake_minimum_required(VERSION 3.10)
project(spdlog_text)

add_executable(main main.cpp)
target_include_directories(main PUBLIC external/spdlog/include)
