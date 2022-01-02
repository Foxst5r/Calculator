cmake_minimum_required(VERSION 3.21)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator main.cpp Token.h Calculator.h)
