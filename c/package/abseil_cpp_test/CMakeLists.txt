cmake_minimum_required(VERSION 3.10)
project(abseil_cpp_test)

add_subdirectory(external/abseil-cpp)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC absl::strings)
