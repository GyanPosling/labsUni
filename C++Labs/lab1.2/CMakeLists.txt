cmake_minimum_required(VERSION 3.10)
project(lab1.2)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/String.cpp
)

set(HEADERS
    include/String.hpp
)

add_executable(lab1.2 ${SOURCES} ${HEADERS})