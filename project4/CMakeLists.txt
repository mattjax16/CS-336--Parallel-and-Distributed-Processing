cmake_minimum_required(VERSION 3.21)
project(project4 C)

set(CMAKE_C_STANDARD 99)


add_executable(project4 src/my_timing.c src/benford_parallel_F_2.c)
set(CMAKE_C_FLAGS "-lpthread")

target_link_libraries(project4 m)
target_link_libraries( project4 pthread )