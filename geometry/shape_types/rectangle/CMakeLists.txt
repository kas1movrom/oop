cmake_minimum_required(VERSION 3.24)
project(rectangle)

set(CMAKE_CXX_STANDARD 17)

add_library(rectangle STATIC source/Rectangle.cpp)

target_include_directories(rectangle PUBLIC include)
target_link_libraries(rectangle PUBLIC abstractShape)