cmake_minimum_required(VERSION 3.24)
project(lab1oop)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(lab1 func.h func.cpp)

link_libraries(lab1)

add_executable(main main.cpp)
