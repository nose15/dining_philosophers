cmake_minimum_required(VERSION 3.30)
project(shared_resources)

set(CMAKE_CXX_STANDARD 20)

add_library(shared_resources)

set_target_properties(shared_resources PROPERTIES LINKER_LANGUAGE CXX)

target_sources(shared_resources
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/shared_resources/Fork.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/shared_resources/ForkArbitrator.hpp
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Fork.cpp
)

target_include_directories(shared_resources
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)