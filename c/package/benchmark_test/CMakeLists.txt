cmake_minimum_required(VERSION 3.10)
project(benchmark_test)

add_executable(main main.cpp)

enable_testing()
add_subdirectory(external/benchmark)
add_executable(bench bench.cpp)
target_link_libraries(bench benchmark::benchmark)
add_test(NAME bench COMMAND bench)
