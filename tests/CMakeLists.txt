# CMake settings
cmake_minimum_required( VERSION 3.15...3.22 )

# Project settings
project( ptc-print-tests
    VERSION 1.0
    DESCRIPTION "Build system for ptc-print tests."
    LANGUAGES CXX
)

# Set c++ standard options
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Set compiler
set( CMAKE_CXX_COMPILER g++ )

# Create executables
if( WIN32 )
    set( SYSTEM "system_tests.exe" )
    set( UNIT "unit_tests.exe" )
    set( THREAD "threading_tests.exe" )
else()
    set( SYSTEM "system_tests" )
    set( UNIT "unit_tests" )
    set( THREAD "threading_tests" )
endif ()

add_executable( ${UNIT} unit_tests.cpp )
add_executable( ${SYSTEM} system_tests.cpp )
add_executable( ${THREAD} threading_tests.cpp )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic -g" )
endif()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Adding specific linker flags
target_link_libraries( threading_tests pthread )
