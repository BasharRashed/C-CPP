cmake_minimum_required(VERSION 3.22)
project(ex2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex2 main.c
        sort_bus_lines.c
        test_bus_lines.c)
