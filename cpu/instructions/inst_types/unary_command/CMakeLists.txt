cmake_minimum_required(VERSION 3.24)
project(unary_command)

set(CMAKE_CXX_STANDARD 17)

add_library(unary_command STATIC src/unary_command.cpp)

target_include_directories(unary_command PUBLIC include)
target_link_libraries(unary_command PUBLIC inst_interface)