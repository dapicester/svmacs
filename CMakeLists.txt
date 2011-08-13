project (svmacs CXX)

set(svmacs_VERSION_MAJOR "0")
set(svmacs_VERSION_MINOR "9")
set(svmacs_VERSION_PATCH "0")

cmake_minimum_required(VERSION 2.8.0)

# find modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_VERBOSE_MAKEFILE OFF CACHE BOOL "verbose make messages")

# The macro below forces the build directory to be different from source directory
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("Project ${PROJECT_NAME} requires an out of source build.")

# default prefix to the "/opt/svmacs" directory
set(CMAKE_INSTALL_PREFIX "/opt/svmacs")
message(STATUS "prefix = ${CMAKE_INSTALL_PREFIX}")

# build libjackcpp
add_subdirectory(libjackcpp)

# build svmacs
add_subdirectory(src)

# build tests
option(ENABLE_TESTING "Enable test compilation" ON)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

# packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${svmacs_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${svmacs_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${svmacs_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_GENERATOR "TGZ")
include(CPack)
