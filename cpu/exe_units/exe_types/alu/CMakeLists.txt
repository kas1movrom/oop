cmake_minimum_required(VERSION 3.24)
project(alu)

set(CMAKE_CXX_STANDARD 17)

add_library(alu STATIC src/arithmetic_logic_unit.cpp)

target_include_directories(alu PUBLIC include)
target_link_libraries(alu PUBLIC exe_interface)