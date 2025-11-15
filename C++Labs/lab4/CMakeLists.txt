cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    models/src/Human.cpp
    models/src/Teacher.cpp
    models/src/CommissionMember.cpp
    models/src/TeacherCommissionMember.cpp
    templates/include/Deque.tpp
    main/main.cpp
)

set(HEADERS
    models/include/Human.hpp
    models/include/Teacher.hpp
    models/include/CommissionMember.hpp
    models/include/TeacherCommissionMember.hpp
    templates/include/Deque.hpp
)

add_executable(lab4 ${SOURCES} ${HEADERS})