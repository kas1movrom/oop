cmake_minimum_required(VERSION 3.24)
project(variable)

set(CMAKE_CXX_STANDARD 17)

add_library(variable STATIC src/variable.cpp)
target_include_directories(variable PUBLIC include)