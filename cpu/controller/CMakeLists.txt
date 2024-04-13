cmake_minimum_required(VERSION 3.24)
project(controller)

set(CMAKE_CXX_STANDARD 17)

add_library(controller STATIC src/controller.cpp)

target_include_directories(controller PUBLIC include)

target_link_libraries(controller PUBLIC view)
target_link_libraries(controller PUBLIC main_service)