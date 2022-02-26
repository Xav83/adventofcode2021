cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode_Day_9)

add_executable(day9_example src/example.cpp)
set_property(TARGET day9_example PROPERTY CXX_STANDARD 17)
target_compile_options(day9_example PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /permissive->)
