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
elseif( APPLE )
    set( INSTALLATION_DIR /usr/local/include )
elseif( WIN32 )
    set( WIN_INSTALLATION_DIR "" CACHE STRING "Installation directory for Windows OSs." )
    set( INSTALLATION_DIR ${WIN_INSTALLATION_DIR} )
endif()

# Installation commands
INSTALL(
    DIRECTORY include/ptc
    DESTINATION ${INSTALLATION_DIR}
)

# Compile tests and benchmarks
add_subdirectory( tests )
