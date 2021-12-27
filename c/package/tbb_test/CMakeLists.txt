cmake_minimum_required(VERSION 3.10)
project(tbb_test)

add_subdirectory(external/oneTBB)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC tbb)
