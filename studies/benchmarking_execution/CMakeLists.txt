# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( ptc-print-benchmarks
    VERSION 1.0
    DESCRIPTION "Build system for ptc-print benchmarking."
    LANGUAGES CXX
)

# Set C++ standard options
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Set compiler
set( CMAKE_CXX_COMPILER g++ )

# Create executables
if( WIN32 )
    set( BENCHMARKING benchmarking.exe )
else()
    set( BENCHMARKING benchmarking )
endif()

add_executable( ${BENCHMARKING} benchmarking.cpp )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd /OX /O1" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-unused-function -Wno-unused-parameter -O3 -O1 -falign-functions=32" )
endif()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Adding specific linker flags
set( LINKER_FLAGS "benchmark" "fmt" )
target_link_libraries( ${BENCHMARKING} ${LINKER_FLAGS} )