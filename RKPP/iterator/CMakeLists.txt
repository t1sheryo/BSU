cmake_minimum_required(VERSION 3.27)
project(iterator)

set(CMAKE_CXX_STANDARD 23)

add_executable(iterator main.cpp
        iterator.h
        iter_imp.cpp)
