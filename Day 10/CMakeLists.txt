cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_10)

add_executable(day10_example src/example.cpp)
set_property(TARGET day10_example PROPERTY CXX_STANDARD 17)
target_compile_options(day10_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
