project(cxx_utils)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wlogical-op -Werror -Weffc++")

link_directories($ENV{GTEST_HOME})
include_directories(include)

add_executable(rand_line
    src/rand_line.cxx)

add_executable(wc
    include/wc.h
    src/wc.cxx
    src/wc_main.cxx)

add_executable(test_wc
    include/wc.h
    src/wc.cxx
    tests/test_wc.cxx)

target_link_libraries(test_wc pthread gtest gtest_main)
