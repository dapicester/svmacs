project (svmacs)

set(svmacs_VERSION_MAJOR "0")
set(svmacs_VERSION_MINOR "9")
set(svmacs_VERSION_PATCH "0")

cmake_minimum_required(VERSION 2.8.0)

# find modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# include modules
include(CMakeDependentOption)
include(MacroBuildInfo)
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("Project ${PROJECT_NAME} requires an out of source build.")

# installation paths
set(INSTALL_BIN  "bin" CACHE STRING "Binary installation directory, relative to prefix")
set(INSTALL_DATA "etc/svmacs" CACHE STRING "Data installation directory, relative to prefix") 
set(INSTALL_LIB  "lib" CACHE STRING "Library installation directory, relative to prefix")
message(STATUS "Installation:")
message(STATUS "  prefix  : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  bindir  : ${INSTALL_BIN}")
message(STATUS "  datadir : ${INSTALL_DATA}") 
message(STATUS "  libdir  : ${INSTALL_LIB}")

# build libjackcpp
add_subdirectory(libjackcpp)

# build svmacs
add_subdirectory(src)

# build tests
option(ENABLE_TESTING "Enable tests compilation" ON)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License")
set(CPACK_PACKAGE_VERSION_MAJOR "${svmacs_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${svmacs_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${svmacs_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_GENERATOR "TGZ")
include(CPack)
