cmake_minimum_required(VERSION 3.24)
project(finallab2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(queuewithmessagesdir)

add_executable(finallab2 main.cpp Dialog/src/dialog.cpp Dialog/include/Dialog/dialog.h)

add_executable(prog_testing tests/tests.cpp ../myvector/tests/catch2.hpp)

target_link_libraries(finallab2 QueueWithMessages)

target_link_libraries(prog_testing QueueWithMessages)