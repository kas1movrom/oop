cmake_minimum_required(VERSION 3.24)
project(cpu_service)

set(CMAKE_CXX_STANDARD 17)

add_library(main_service STATIC src/main_service.cpp)

target_include_directories(main_service PUBLIC include)

target_link_libraries(main_service PUBLIC parse_service)
target_link_libraries(main_service PUBLIC cpu_service)

