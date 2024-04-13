cmake_minimum_required(VERSION 3.24)
project(cpu)

set(CMAKE_CXX_STANDARD 17)

add_library(cpu STATIC src/cpu.cpp)

target_include_directories(cpu PUBLIC include)

target_link_libraries(cpu PUBLIC program_memory)
target_link_libraries(cpu PUBLIC core)