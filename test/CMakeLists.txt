# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

cmake_dependent_option(ENABLE_ALL_TESTS "Compile all tests" OFF "ENABLE_TESTING" OFF)

find_package(JACK REQUIRED)
if(NOT JACK_FOUND)
    message(FATAL_ERROR "JACK not found.")
endif()

find_package(ITPP REQUIRED)
if(NOT ITPP_FOUND)
    message(FATAL_ERROR "IT++ not found.")
endif()

find_package(LibSVM REQUIRED)
if(NOT LIBSVM_FOUND)
    message(FATAL_ERROR "LibSVM not found.")
endif()

find_package(RLog REQUIRED)
if (NOT RLOG_FOUND)
    message(FATAL_ERROR "RLog not found.")
endif()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/include
    ${SOURCE_DIR}
    ${TEST_DIR})
include_directories(${INCLUDE_DIR})

set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)
set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

#set(MFCC_FILE OFF)

configure_file(${SOURCE_DIR}/config.h.in config.h)
configure_file(testconfig.h.in testconfig.h)
include_directories(${CMAKE_BINARY_DIR}/test)
add_definitions(-g)

# TODO: fix this macro
# usage: add_unit_test(source.cpp lib1 lib2)
#macro(add_unit_test)
#    set(TEST ${ARGV0})
#    message(STATUS "  found test: ${TEST}")
#    get_filename_component(TestName ${TEST} NAME_WE)
#    add_executable(${TestName} ${TEST})
#    target_link_libraries(${TestName} ${ARGV1})
#    add_test(NAME ${TestName} COMMAND ${TestName})
#    #message(STATUS "* added test: ${TestName}")
#endmacro(add_unit_test)

cmake_dependent_option(ENABLE_LIB_TEST "Compile libraries tests" OFF "ENABLE_TESTING" OFF)
if (ENABLE_LIB_TEST OR ENABLE_ALL_TESTS)
    add_subdirectory(lib)
endif()

cmake_dependent_option(ENABLE_CORE_TEST "Compile core tests" ON "ENABLE_TESTING" OFF)
if (ENABLE_CORE_TEST OR ENABLE_ALL_TESTS)
    add_subdirectory(core)
endif()

cmake_dependent_option(ENABLE_FEATURE_TEST "Compile features tests" ON "ENABLE_TESTING" OFF)
if (ENABLE_FEATURE_TEST OR ENABLE_ALL_TESTS)
    add_subdirectory(features)
endif()

cmake_dependent_option(ENABLE_MATLAB_TEST "Compile matlab test tool" OFF "ENABLE_TESTING" OFF)
if (ENABLE_MATLAB_TEST)
    add_subdirectory(matlab)
endif()

