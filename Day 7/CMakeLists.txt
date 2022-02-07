cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_7)

add_executable(day7_example src/example.cpp)
set_property(TARGET day7_example PROPERTY CXX_STANDARD 17)
target_compile_options(day7_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)

add_executable(day7_part1 src/part1.cpp)
set_property(TARGET day7_part1 PROPERTY CXX_STANDARD 17)
target_compile_options(day7_part1 PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
