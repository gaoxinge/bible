cmake_minimum_required(VERSION 3.10)
project(glog_test)

add_subdirectory(external/glog)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC glog::glog)
