cmake_minimum_required(VERSION 3.30)
project(dining_philosophers)

set(CMAKE_CXX_STANDARD 20)

add_executable(dining_philosophers main.cpp)
add_subdirectory(core)

target_link_libraries(dining_philosophers
    core
)