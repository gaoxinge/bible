cmake_minimum_required(VERSION 3.10)
project(boost_test)

set(BOOST_ROOT /c/gaoxinge/bin/boost_1_77_0)

find_package(Boost COMPONENTS iostreams REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${Boost_LIBRARIES})
