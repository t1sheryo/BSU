cmake_minimum_required(VERSION 3.27)
project(rashet_graph_rabota)

set(CMAKE_CXX_STANDARD 23)

add_executable(rashet_graph_rabota main.cpp
        Bank.h
        Bank_implentation.cpp
        MyException.h)
