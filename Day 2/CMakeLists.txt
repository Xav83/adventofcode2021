cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_2)

add_executable(day2_example src/example.cpp)
set_property(TARGET day2_example PROPERTY CXX_STANDARD 17)
target_compile_options(day2_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day2_part1 src/part1.cpp)
set_property(TARGET day2_part1 PROPERTY CXX_STANDARD 17)
target_compile_options(day2_part1 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day2_part2 src/part2.cpp)
set_property(TARGET day2_part2 PROPERTY CXX_STANDARD 17)
target_compile_options(day2_part2 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
