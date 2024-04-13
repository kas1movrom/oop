cmake_minimum_required(VERSION 3.24)
project(square)

set(CMAKE_CXX_STANDARD 17)

add_library(square STATIC source/Square.cpp)

target_include_directories(square PUBLIC include)
target_link_libraries(square PUBLIC rectangle)
