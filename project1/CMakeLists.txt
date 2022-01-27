cmake_minimum_required(VERSION 3.21)
project(project1 C)

set(CMAKE_C_STANDARD 99)

add_executable(project1 src/my_math.c src/test_my_math.c)
