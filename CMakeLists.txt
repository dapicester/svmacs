project (svmacs CXX)

cmake_minimum_required(VERSION 2.8.0)

# find modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_VERBOSE_MAKEFILE OFF)
#set(DEBUG ON)

# The macro below forces the build directory to be different from source directory:
#include(MacroOutOfSourceBuild)
#macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

# build libjackcpp
add_subdirectory(libjackcpp)

# build svmacs
add_subdirectory(src)

set (ENABLE_TESTING TRUE)
if (ENABLE_TESTING)
    add_subdirectory(test)
    enable_testing()
endif()
