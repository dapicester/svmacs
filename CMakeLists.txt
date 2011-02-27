project (svmacs)

cmake_minimum_required(VERSION 2.6.0)

# find modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_VERBOSE_MAKEFILE ON)
# add_definitions(-DENABLE_DEBUG)
set (DEBUG ON)
add_definitions(-DENABLE_LOG)

# The macro below forces the build directory to be different from source directory:
#include(MacroOutOfSourceBuild)
#macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

add_subdirectory(src)

set (ENABLE_TESTING TRUE)
if (ENABLE_TESTING)
    add_subdirectory(test)
    enable_testing()
endif()
