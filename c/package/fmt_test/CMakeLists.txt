cmake_minimum_required(VERSION 3.10)
project(fmt_test)

add_subdirectory(external/fmt)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC fmt)
# target_link_libraries(main PUBLIC fmt::fmt-header-only)
