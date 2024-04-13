cmake_minimum_required(VERSION 3.24)
project(ellipse)

set(CMAKE_CXX_STANDARD 17)

add_library(ellipse STATIC source/Ellipse.cpp)

target_include_directories(ellipse PUBLIC include)
target_link_libraries(ellipse PUBLIC abstractShape)