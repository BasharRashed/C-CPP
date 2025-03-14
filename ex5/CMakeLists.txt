cmake_minimum_required(VERSION 3.22)
project(ex5)

set(CMAKE_CXX_STANDARD 20)

add_executable(ex5
        Movie.h
        RecommendationSystem.h
        RecommendationSystemLoader.h
        User.h
        UsersLoader.h
        Movie.cpp
        User.cpp
        RecommendationSystem.cpp
        RecommendationSystemLoader.cpp
        UsersLoader.cpp)
