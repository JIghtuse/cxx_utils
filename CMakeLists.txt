project(cxx_utils)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Weffc++ -Wshadow")
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
endif()

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

add_executable(bulls_and_cows
    src/bulls_and_cows.cxx)

find_package(Boost 1.58 COMPONENTS system filesystem REQUIRED)

add_executable(lurker
    src/lurker.cxx)

target_link_libraries(lurker
    ${Boost_SYSTEM_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARIES}
)
