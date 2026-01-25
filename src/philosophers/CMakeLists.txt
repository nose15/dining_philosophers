cmake_minimum_required(VERSION 3.30)
project(philosophers)

set(CMAKE_CXX_STANDARD 20)

add_library(philosophers)

target_sources(philosophers
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/ArbitratorCallEatMethod.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/HierarchyEatMethod.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/IEatMethod.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/NoSyncEatMethod.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/Philosopher.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/ScopedLockEatMethod.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/philosophers/State.hpp
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ArbitratorCallEatMethod.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/HierarchyEatMethod.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NoSyncEatMethod.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Philosopher.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ScopedLockEatMethod.cpp

)

target_include_directories(philosophers
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(philosophers
            shared_resources
)
