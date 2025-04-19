cmake_minimum_required(VERSION 3.22)
project(ex3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex3
        markov_chain.c
        tweets_generator.c
        linked_list.c)
