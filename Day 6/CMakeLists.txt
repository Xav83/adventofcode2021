cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_6)

add_executable(day6_example src/example.cpp)
set_property(TARGET day6_example PROPERTY CXX_STANDARD 17)
target_compile_options(day6_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day6_part1 src/part1.cpp)
set_property(TARGET day6_part1 PROPERTY CXX_STANDARD 17)
target_compile_options(day6_part1 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day6_part2 src/part2.cpp)
set_property(TARGET day6_part2 PROPERTY CXX_STANDARD 17)
target_compile_options(day6_part2 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
