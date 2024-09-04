cmake_minimum_required(VERSION 3.27)
project(move_semantics)

set(CMAKE_CXX_STANDARD 23)

add_executable(move_semantics main.cpp
        Animal.h)
