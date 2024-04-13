cmake_minimum_required(VERSION 3.24)
project(core)

set(CMAKE_CXX_STANDARD 17)

add_library(core STATIC src/core.cpp)
target_include_directories(core PUBLIC include)

target_link_libraries(core PUBLIC alu)
target_link_libraries(core PUBLIC fpu)
target_link_libraries(core PUBLIC bs)