cmake_minimum_required(VERSION 3.24)
project(circle)

set(CMAKE_CXX_STANDARD 17)

add_library(circle STATIC source/Circle.cpp)

target_include_directories(circle PUBLIC include)
target_link_libraries(circle PUBLIC ellipse)
