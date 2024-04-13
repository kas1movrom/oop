cmake_minimum_required(VERSION 3.24)
project(abstractShape)

set(CMAKE_CXX_STANDARD 17)

add_library(abstractShape INTERFACE)

target_include_directories(abstractShape INTERFACE include)
target_link_libraries(abstractShape INTERFACE point)
