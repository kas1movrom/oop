cmake_minimum_required(VERSION 3.24)
project(inst_interface)

set(CMAKE_CXX_STANDARD 17)

add_library(inst_interface STATIC src/instruction.cpp)

target_include_directories(inst_interface PUBLIC include)
target_link_libraries(inst_interface PUBLIC variable)