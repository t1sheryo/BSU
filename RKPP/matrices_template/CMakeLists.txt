cmake_minimum_required(VERSION 3.27)
project(matrices_template)

set(CMAKE_CXX_STANDARD 23)

add_executable(matrices_template main.cpp
        Matrix.h
        Rational.h
        SquareMatrix.h
        SquareMatrix.h
        MyException.h
        Rational_implementation.cpp
)
