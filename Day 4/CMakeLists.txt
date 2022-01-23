cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_4)

add_executable(day4_example src/example.cpp)
set_property(TARGET day4_example PROPERTY CXX_STANDARD 17)

add_executable(day4_part1 src/part1.cpp)
set_property(TARGET day4_part1 PROPERTY CXX_STANDARD 17)
