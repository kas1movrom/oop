cmake_minimum_required(VERSION 3.24)
project(fpu)

set(CMAKE_CXX_STANDARD 17)

add_library(fpu STATIC src/floating_point_unit.cpp)

target_include_directories(fpu PUBLIC include)
target_link_libraries(fpu PUBLIC exe_interface)