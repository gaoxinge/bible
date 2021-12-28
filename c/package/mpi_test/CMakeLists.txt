cmake_minimum_required(VERSION 3.10)
project(mpi_test)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${MPI_LIBRARIES})
