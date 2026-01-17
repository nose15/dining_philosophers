cmake_minimum_required(VERSION 3.30)
project(dining_philosophers_entities)

add_library(dining_philosophers_entities)

set(CMAKE_CXX_STANDARD 20)

target_sources(dining_philosophers_entities
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/dining_philosophers_entities/Fork.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/dining_philosophers_entities/Philosopher.hpp
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Philosopher.cpp
)

target_include_directories(dining_philosophers_entities
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)