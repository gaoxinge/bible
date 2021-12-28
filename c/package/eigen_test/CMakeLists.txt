cmake_minimum_required(VERSION 3.10)
project(eigen_test)

add_subdirectory(external/eigen)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC Eigen3::Eigen)
