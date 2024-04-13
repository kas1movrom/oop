cmake_minimum_required(VERSION 3.24)
project(binary_command)

set(CMAKE_CXX_STANDARD 17)

add_library(binary_command STATIC src/binary_command.cpp)

target_include_directories(binary_command PUBLIC include)
target_link_libraries(binary_command PUBLIC inst_interface)