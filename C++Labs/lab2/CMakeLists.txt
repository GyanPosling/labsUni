cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Array.cpp
)

set(HEADERS
    include/Array.h
)

add_executable(lab2 ${SOURCES} ${HEADERS})