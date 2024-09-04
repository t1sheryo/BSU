cmake_minimum_required(VERSION 3.27)
project(0variant)

set(CMAKE_CXX_STANDARD 23)

add_executable(0variant main.cpp
        header.h
        implementation.cpp
        Magician.h
        Magician_implementation.cpp)
