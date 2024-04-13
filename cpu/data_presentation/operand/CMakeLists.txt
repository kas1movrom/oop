cmake_minimum_required(VERSION 3.24)
project(operand)

set(CMAKE_CXX_STANDARD 17)

add_library(operand STATIC src/operand.cpp)
target_include_directories(operand PUBLIC include)