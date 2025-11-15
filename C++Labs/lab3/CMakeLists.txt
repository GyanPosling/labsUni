cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    src/Human.cpp
    src/Teacher.cpp
    src/CommissionMember.cpp
    src/TeacherCommissionMember.cpp
    main/main.cpp
)

set(HEADERS
    include/Human.hpp
    include/Teacher.hpp
    include/CommissionMember.hpp
    include/TeacherCommissionMember.hpp
)

add_executable(lab3 ${SOURCES} ${HEADERS})