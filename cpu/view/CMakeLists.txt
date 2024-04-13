cmake_minimum_required(VERSION 3.24)
project(view)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/romka/sfml/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window audio graphics network REQUIRED)

add_library(view STATIC src/view.cpp)

target_include_directories(view PUBLIC include)
target_link_libraries(view sfml-system sfml-window sfml-audio sfml-graphics sfml-network)
