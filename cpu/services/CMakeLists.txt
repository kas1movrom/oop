cmake_minimum_required(VERSION 3.24)
project(services)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(parse_service)
add_subdirectory(main_service)
add_subdirectory(cpu_service)