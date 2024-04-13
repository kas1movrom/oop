cmake_minimum_required(VERSION 3.24)
project(data_memory)

set(CMAKE_CXX_STANDARD 17)

add_library(data_memory STATIC src/data_memory.cpp)

target_include_directories(data_memory PUBLIC include)
target_link_libraries(data_memory PUBLIC operand)