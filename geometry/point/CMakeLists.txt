cmake_minimum_required(VERSION 3.24)
project(point)

set(CMAKE_CXX_STANDARD 17)

add_library(point STATIC source/Point.cpp)

target_include_directories(point PUBLIC include)