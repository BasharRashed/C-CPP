cmake_minimum_required(VERSION 3.22)
project(newex3b C)

set(CMAKE_C_STANDARD 99)

add_executable(newex3b
        linked_list.c
        markov_chain.c
        tweets_generator.c
        snakes_and_ladders.c)
