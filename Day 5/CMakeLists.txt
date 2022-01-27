cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_5)

add_executable(day5_example src/example.cpp)
set_property(TARGET day5_example PROPERTY CXX_STANDARD 17)

add_executable(day5_part1 src/part1.cpp)
set_property(TARGET day5_part1 PROPERTY CXX_STANDARD 17)
