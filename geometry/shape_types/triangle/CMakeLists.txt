cmake_minimum_required(VERSION 3.24)
project(triangle)

set(CMAKE_CXX_STANDARD 17)

add_library(triangle STATIC source/Triangle.cpp)

target_include_directories(triangle PUBLIC include)
target_link_libraries(triangle PUBLIC abstractShape)