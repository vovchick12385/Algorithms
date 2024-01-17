cmake_minimum_required(VERSION 3.27)
project(src)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(src
        main.cpp
        HierarchicalMutex/Hierarchical_mutex.cpp)
