cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_8)

add_executable(day8_example src/example.cpp)
set_property(TARGET day8_example PROPERTY CXX_STANDARD 17)
target_compile_options(day8_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day8_part1 src/part1.cpp)
set_property(TARGET day8_part1 PROPERTY CXX_STANDARD 17)
target_compile_options(day8_part1 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day8_part2 src/part2.cpp)
set_property(TARGET day8_part2 PROPERTY CXX_STANDARD 17)
target_compile_options(day8_part2 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
