cmake_minimum_required(VERSION 3.30)
project(core)

set(CMAKE_CXX_STANDARD 20)

add_library(core)

target_sources(core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/core/DiningPhilosophers.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Fork.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Philosopher.hpp
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/DiningPhilosophers.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Philosopher.cpp
)

target_include_directories(core
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)