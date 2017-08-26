project(cxx_utils)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Weffc++ -Wshadow")
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
endif()

link_directories($ENV{GTEST_HOME})
include_directories(include)
include_directories(/usr/include/gtest)

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

find_package(Boost 1.58 COMPONENTS system filesystem program_options REQUIRED)

add_executable(lurker
    src/lurker.cxx)

target_link_libraries(lurker
    ${Boost_SYSTEM_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARIES}
)

add_executable(xml_value
    src/xml_value.cxx)

target_link_libraries(xml_value
    tinyxml)

add_executable(pp
    src/pp.cxx)

target_link_libraries(pp
    ${Boost_SYSTEM_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARIES}
    ${Boost_PROGRAM_OPTIONS_LIBRARIES}
)

add_executable(rand_int
    src/rand_int.cxx)

add_executable(cities
    include/color.h
    src/cities.cxx)

add_executable(url_extractor
    src/url_extractor.cxx)

target_link_libraries(url_extractor
    ${Boost_PROGRAM_OPTIONS_LIBRARIES}
)

add_executable(ls
    src/ls.cxx)

target_link_libraries(ls
    stdc++fs
)

add_executable(valid_ip_address
    src/valid_ip_address.cxx)

target_link_libraries(valid_ip_address
    Boost::program_options
    Boost::system
)

add_executable(number_statistics
    src/number_statistics.cxx)
