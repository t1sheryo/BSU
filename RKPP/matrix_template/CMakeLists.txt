cmake_minimum_required(VERSION 3.27)
project(matrix_template)

set(CMAKE_CXX_STANDARD 23)

add_executable(matrix_template main.cpp
        MyException.h
        Matrix.h
        Rational.h
        Rational_implementation.cpp
        SquareMatrix.h)
