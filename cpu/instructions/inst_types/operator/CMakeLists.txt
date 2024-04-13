cmake_minimum_required(VERSION 3.24)
project(operator)

set(CMAKE_CXX_STANDARD 17)

add_library(operator STATIC src/operator.cpp)

target_include_directories(operator PUBLIC include)
target_link_libraries(operator PUBLIC inst_interface)