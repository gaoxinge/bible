cmake_minimum_required(VERSION 3.10)
project(google_test_test)

add_executable(main main.cpp)

enable_testing()
add_subdirectory(external/googletest)
# add_executable(hello_test test1.cpp test2.cpp)
add_executable(hello_test test.cpp test1.cpp test2.cpp)
target_link_libraries(hello_test gtest_main)
add_test(NAME hello_test COMMAND hello_test)
