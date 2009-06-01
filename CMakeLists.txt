project (svmacs)

cmake_minimum_required(VERSION 2.6.0)

#set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(-DENABLE_DEBUG)

find_package(Qt4 REQUIRED)

add_subdirectory(src)

#set (ENABLE_TESTING TRUE)

if (ENABLE_TESTING)
    add_subdirectory(test)
    enable_testing()
endif()
