cmake_minimum_required(VERSION 3.22)
project(ex1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 main.c
        cipher.c
        tests.c)
