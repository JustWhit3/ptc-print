# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( ptc-print-build
    VERSION 1.0
    DESCRIPTION "Build system for ptc-print."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Choosing appropriate installation directory
if( UNIX )
    set( INSTALLATION_DIR /usr/include )
    set( CMAKE_DIR /usr/lib/cmake )
elseif( APPLE )
    set( INSTALLATION_DIR /usr/local/include )
    set( CMAKE_DIR /usr/lib/cmake )
elseif( WIN32 )
    set( WIN_INSTALLATION_DIR "" CACHE STRING "Installation directory for Windows OSs." )
    set( INSTALLATION_DIR ${WIN_INSTALLATION_DIR} )
    set( WIN_CMAKE_DIR "" CACHE STRING "Cmake library directory for Windows OSs." )
    set( CMAKE_DIR ${WIN_CMAKE_DIR} )
endif()

# Installation commands
install(
    FILES include/ptc/print.hpp
    DESTINATION ${INSTALLATION_DIR}/ptc
)

install(
    FILES scripts/cmake/ptc-print-config.cmake
    DESTINATION ${CMAKE_DIR}/ptc-print
)

# Compile tests and benchmarks
add_subdirectory( tests )
