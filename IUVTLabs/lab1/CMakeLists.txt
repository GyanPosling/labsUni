cmake_minimum_required(VERSION 3.16)

project(PowerMonitorA4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 QUIET COMPONENTS Widgets)

if(Qt6_FOUND)
    set(QT_PACKAGE Qt6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    set(QT_PACKAGE Qt5)
endif()

add_executable(PowerMonitorA4 WIN32
    src/main.cpp
    src/power_widget.cpp
    src/power_manager.cpp
    src/log_window.cpp
    include/power_widget.h
    include/power_manager.h
    include/log_window.h
)

target_include_directories(PowerMonitorA4 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(PowerMonitorA4 PRIVATE
    ${QT_PACKAGE}::Widgets
    PowrProf
    Setupapi
    Advapi32
)

find_program(WINDEPLOYQT_EXECUTABLE
    NAMES windeployqt windeployqt6
    HINTS "${CMAKE_PREFIX_PATH}/bin"
)

if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET PowerMonitorA4 POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                --no-translations
                "$<TARGET_FILE:PowerMonitorA4>"
        COMMENT "Deploying Qt runtime files"
    )
endif()

if(MINGW)
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    foreach(RUNTIME_DLL
        libgcc_s_seh-1.dll
        libstdc++-6.dll
        libwinpthread-1.dll
        libb2-1.dll
        libbrotlicommon.dll
        libbrotlidec.dll
        libbz2-1.dll
        libdouble-conversion.dll
        libfreetype-6.dll
        libglib-2.0-0.dll
        libgraphite2.dll
        libharfbuzz-0.dll
        libicudt78.dll
        libicuin78.dll
        libicuuc78.dll
        libintl-8.dll
        libmd4c.dll
        libpcre2-16-0.dll
        libpcre2-8-0.dll
        libpng16-16.dll
        zlib1.dll
        libzstd.dll
    )
        if(EXISTS "${MINGW_BIN_DIR}/${RUNTIME_DLL}")
            add_custom_command(TARGET PowerMonitorA4 POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${MINGW_BIN_DIR}/${RUNTIME_DLL}"
                        "$<TARGET_FILE_DIR:PowerMonitorA4>"
            )
        endif()
    endforeach()
endif()

if(MSVC)
    target_compile_options(PowerMonitorA4 PRIVATE /utf-8)
endif()
