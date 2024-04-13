cmake_minimum_required(VERSION 3.24)
project(bs)

set(CMAKE_CXX_STANDARD 17)

add_library(bs STATIC src/base_shifter.cpp)

target_include_directories(bs PUBLIC include)
target_link_libraries(bs PUBLIC exe_interface)