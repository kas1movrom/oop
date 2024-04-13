cmake_minimum_required(VERSION 3.24)
project(parse_service)

set(CMAKE_CXX_STANDARD 17)

add_library(parse_service STATIC src/parse_service.cpp)

target_include_directories(parse_service PUBLIC include)
