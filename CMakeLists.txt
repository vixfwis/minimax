cmake_minimum_required(VERSION 3.10)
project(minimax)

set(CMAKE_CXX_STANDARD 17)

add_executable(minimax main.cpp board.hpp)
add_executable(minimax_tests tests/minimax_tests.cpp board.hpp)
