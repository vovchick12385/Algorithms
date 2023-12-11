cmake_minimum_required(VERSION 3.27)

project(algorithms
        LANGUAGES CXX)

set(CMAKE_CXX_STANDATD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(src)

add_executable(algorithms
        src/main.cpp
        src/IKVDatabases.h
        src/Multithreading_queue.cpp
        src/Task.h
)