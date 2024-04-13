cmake_minimum_required(VERSION 3.24)
project(cpu_final)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(components)
add_subdirectory(cpu)
add_subdirectory(data_presentation)
add_subdirectory(exe_units)
add_subdirectory(instructions)
add_subdirectory(app)
add_subdirectory(services)

add_subdirectory(controller)
add_subdirectory(view)
