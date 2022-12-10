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

# Create interface library
add_library( ptcprint INTERFACE )
add_library( ptcprint::ptcprint ALIAS ptcprint )

# Compile tests
option( PTCPRINT_TESTS "Enable / disable tests." ON )
if( PTCPRINT_TESTS )
    add_subdirectory( tests )
else()
    message( STATUS "Skipping tests." )
endif()

# Setting installation paths
target_include_directories( ptcprint INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(
    DIRECTORY include/ptc
    DESTINATION include
)

# Creating the package files
install( 
    TARGETS ptcprint
    EXPORT ptcprintTargets
    DESTINATION lib
)

install(
    EXPORT ptcprintTargets
    FILE ptcprintTargets.cmake
    NAMESPACE ptcprint::
    DESTINATION lib/cmake/ptcprint
)

# Configure package files
include( CMakePackageConfigHelpers )

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/ptcprintConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/ptcprint"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ptcprintConfigVersion.cmake"
  VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install( FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ptcprintConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ptcprintConfigVersion.cmake
    DESTINATION lib/cmake/ptcprint
)

export( EXPORT ptcprintTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/ptcprintTargets.cmake"
)