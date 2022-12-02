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


# Compile tests
add_subdirectory( tests )

# Create interface library
add_library( ptcprint INTERFACE )
add_library( ptcprint::ptcprint ALIAS ptcprint )

# Installing headers
if( UNIX )
    set( INSTALLATION_DIR_INCLUDE /usr/include )
elseif( APPLE )
    set( INSTALLATION_DIR_INCLUDE /usr/local/include )
elseif( WIN32 )
    set( WIN_INSTALLATION_DIR_INCLUDE "" CACHE STRING "Installation directory for Windows OSs." )
    set( INSTALLATION_DIR_INCLUDE ${WIN_INSTALLATION_DIR_INCLUDE} )
endif()

install(
    FILES include/ptc/print.hpp
    DESTINATION ${INSTALLATION_DIR_INCLUDE}/ptc
)

# Installing libraries
if( UNIX )
    set( INSTALLATION_DIR_LIB /usr/lib )
elseif( APPLE )
    set( INSTALLATION_DIR_LIB /usr/local/lib )
elseif( WIN32 )
    set( WIN_INSTALLATION_DIR_LIB "" CACHE STRING "Installation directory for Windows OSs." )
    set( INSTALLATION_DIR_LIB ${WIN_INSTALLATION_DIR_LIB} )
endif()

# Creating the package files
install( 
    TARGETS ptcprint
    EXPORT ptcprintTargets
    DESTINATION ${INSTALLATION_DIR_LIB}
)

install(
    EXPORT ptcprintTargets
    FILE ptcprintTargets.cmake
    NAMESPACE ptcprint::
    DESTINATION ${INSTALLATION_DIR_LIB}/cmake/ptcprint
)

# Configure package files
include( CMakePackageConfigHelpers )

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/ptcprintConfig.cmake"
    INSTALL_DESTINATION "${INSTALLATION_DIR_LIB}/cmake/ptcprint"
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
    DESTINATION ${INSTALLATION_DIR_LIB}/cmake/ptcprint
)

export( EXPORT ptcprintTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/ptcprintTargets.cmake"
)