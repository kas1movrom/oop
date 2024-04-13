cmake_minimum_required(VERSION 3.24)
project(exe_interface)

set(CMAKE_CXX_STANDARD 17)

add_library(exe_interface STATIC src/exe_unit.cpp)
target_include_directories(exe_interface PUBLIC include)
target_include_directories(exe_interface PUBLIC ../../vector/include)

target_link_libraries(exe_interface PUBLIC binary_command)
target_link_libraries(exe_interface PUBLIC unary_command)
target_link_libraries(exe_interface PUBLIC data_memory)