cmake_minimum_required(VERSION 3.24)
project(cpu_service)

set(CMAKE_CXX_STANDARD 17)

add_library(cpu_service STATIC src/cpu_service.cpp)

target_include_directories(cpu_service PUBLIC include)

target_link_libraries(cpu_service PUBLIC cpu)