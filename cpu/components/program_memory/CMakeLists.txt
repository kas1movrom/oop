cmake_minimum_required(VERSION 3.24)
project(program_memory)

set(CMAKE_CXX_STANDARD 17)

add_library(program_memory STATIC src/program_memory.cpp)
target_include_directories(program_memory PUBLIC include)

target_link_libraries(program_memory PUBLIC binary_command)
target_link_libraries(program_memory PUBLIC unary_command)
target_link_libraries(program_memory PUBLIC operator)