# CMake settings
cmake_minimum_required( VERSION 3.15 )

# Project settings
project( ptc-print-build
    VERSION 1.0
    DESCRIPTION "Build system for ptc-print."
    LANGUAGES CXX
)

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

# Running tests
find_package( doctest )
if( doctest_FOUND )
    add_subdirectory( tests )
else()
    message( WARNING "Doctest not found, not building tests." )
endif()

# Running benchmarks
find_package( benchmark )
if( benchmark_FOUND )
add_subdirectory( studies/benchmarking_execution )
else()
    message( WARNING "Google Benchmark not found, not building benchmarks." )
endif()