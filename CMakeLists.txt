cmake_minimum_required(VERSION 3.21)
project(CS336_Parallel C)

set(CMAKE_C_STANDARD 11)

include_directories(project1)

set(GCC_COVERAGE_COMPILE_FLAGS "-lm")
add_executable(CS336_Parallel
        project1/src/my_math.c
        project1/src/my_math.h
        project1/src/test_my_math.c)

