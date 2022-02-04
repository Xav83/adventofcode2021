cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_1)

add_executable(day1_example src/example.cpp)
set_property(TARGET day1_example PROPERTY CXX_STANDARD 17)
target_compile_options(day1_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day1_part1 src/part1.cpp)
set_property(TARGET day1_part1 PROPERTY CXX_STANDARD 17)
target_compile_options(day1_part1 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day1_part2 src/part2.cpp)
set_property(TARGET day1_part2 PROPERTY CXX_STANDARD 17)
target_compile_options(day1_part2 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
