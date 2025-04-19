cmake_minimum_required(VERSION 3.22)
project(ex4)

set(CMAKE_CXX_STANDARD 20)

add_executable(ex4 main.cpp
        MlpNetwork.h
        Matrix.cpp
        Activation.cpp
        Activation.h
        Dense.h
        Dense.cpp
        MlpNetwork.cpp
        presubmit.cpp
)
