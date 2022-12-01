# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( ptc-print-tests
    VERSION 1.0
    DESCRIPTION "Build system for ptc-print tests."
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
include_directories( .. )

# Set c++ standard options
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Create executables
if( WIN32 )
    set( SYSTEM "system_tests.exe" )
    set( UNIT "unit_tests.exe" )
    set( THREAD "threading_tests.exe" )
else()
    set( SYSTEM "system_tests" )
    set( UNIT "unit_tests" )
    set( THREAD "threading_tests" )
endif()

add_executable( ${UNIT} unit_tests.cpp )
add_executable( ${SYSTEM} system_tests.cpp )
add_executable( ${THREAD} threading_tests.cpp )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic" )
endif()

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Fetching doctest
find_package( doctest )

if( NOT doctest_FOUND )
    include(FetchContent)
    FetchContent_Declare(
      doctest
      GIT_REPOSITORY "https://github.com/doctest/doctest"
      GIT_TAG master
    )
    message( STATUS "Fetching doctest..." )
    FetchContent_MakeAvailable( doctest )
endif()

# Adding specific linker flags
find_package( Threads )
target_link_libraries( ${THREAD} PRIVATE Threads::Threads )
target_link_libraries( ${UNIT} PRIVATE doctest::doctest )

