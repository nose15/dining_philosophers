cmake_minimum_required(VERSION 3.30)
project(core)

set(CMAKE_CXX_STANDARD 20)

add_library(core)

target_sources(core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/core/DiningPhilosophers.hpp
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/DiningPhilosophers.cpp
)

target_include_directories(core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core
        philosophers
        shared_resources
)