cmake_minimum_required(VERSION 3.9)
project(DestlerDoubloons)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Weffc++ -pedantic -g")

set(DD_PART1_SOURCE_FILES
        src/building_one.cpp
        src/destler_doubloon.cpp
        src/dd_main.cpp
        src/rng.cpp
        src/the_loop.cpp)
add_executable(DD_Part1 ${DD_PART1_SOURCE_FILES})

set(DD_PART2_SOURCE_FILES
        src2/building_one.cpp
        src2/destler_doubloon.cpp
        src2/dd_main.cpp
        src2/rng.cpp
        src2/the_loop.cpp)
add_executable(DD_Part2 ${DD_PART2_SOURCE_FILES})
