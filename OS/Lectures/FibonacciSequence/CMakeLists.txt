cmake_minimum_required(VERSION 3.15 FATAL_ERROR) # Requires CMake 3.15 or higher for modern commands

set(CMAKE_TOOLCHAIN_FILE "C:/proga/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file") # Path to vcpkg toolchain

# Указываем проект
project(FibonacciSequencePrinter)

# Find GTest using vcpkg
find_package(GTest REQUIRED)

# Основной исполняемый файл
add_executable(SeqPrinter solution/solution.cpp
solution/Fibonacci.h
solution/Fibonacci.cpp
)

# Исполняемый файл для тестов
add_executable(FibonacciTests solution/Tests.cpp
solution/Fibonacci.h
solution/Fibonacci.cpp
)

# Связываем тесты с Google Test
target_link_libraries(FibonacciTests GTest::gtest_main)

# Remove FetchContent block
