# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( ptc-print-benchmarks
    VERSION 1.0
    DESCRIPTION "Build system for ptc-print benchmarking."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Other settings for paths
include_directories( ../.. )

# Set C++ standard options
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Create executables
if( WIN32 )
    set( CMAKE_EXECUTABLE_SUFFIX ".exe" )
endif()
set( BENCHMARKING "benchmarking" )
add_executable( ${BENCHMARKING} benchmarking.cpp )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd /OX /O1" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-unused-function -Wno-unused-parameter -O3 -O1 -falign-functions=32" )
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Compiling with the correct standard
set_property( TARGET ${BENCHMARKING} PROPERTY CXX_STANDARD 17 )

# Adding specific linker flags
find_package( benchmark )
find_package( fmt )
target_link_libraries( ${BENCHMARKING} benchmark fmt )
