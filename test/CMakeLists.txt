cmake_minimum_required(VERSION 2.8)

message (STATUS "Tests:")
enable_testing()

# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(ENABLE_ALL_TESTS "Compile all tests" OFF)

################
# dependencies #
################

include_directories("${PROJECT_SOURCE_DIR}/libjackcpp")
set(JACKCPP_LIBRARIES "jackcpp")

find_package( Boost 1.46.0 COMPONENTS signals thread program_options system filesystem REQUIRED )
if ( NOT Boost_FOUND )
    message(FATAL_ERROR "Boost Signals library required, but not found!")
endif (NOT Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})

find_package(RLog REQUIRED)
if ( NOT RLOG_FOUND )
    message(FATAL_ERROR "Package RLog required, but not found!")
endif( NOT RLOG_FOUND )
include_directories(${RLOG_INCLUDE_DIRS})

find_package(LibSVM REQUIRED)
if ( NOT LIBSVM_FOUND )
    message(FATAL_ERROR "Package LibSVM required, but not found!")
endif( NOT LIBSVM_FOUND )
include_directories(${LIBSVM_INCLUDE_DIRS})

find_package(JACK REQUIRED)
if ( NOT JACK_FOUND )
    message(FATAL_ERROR "Package JACK required, but not found!")
endif( NOT JACK_FOUND )
include_directories(${JACK_INCLUDE_DIRS})

find_package(ITPP REQUIRED)
if ( NOT ITPP_FOUND )
    message(FATAL_ERROR "Package IT++ required, but not found!")
endif( NOT ITPP_FOUND )
include_directories(${ITPP_INCLUDE_DIRS})

find_package(CppUnit REQUIRED)
if ( NOT CPPUNIT_FOUND )
    message(FATAL_ERROR "Package CppUnit required, but not found!")
endif( NOT CPPUNIT_FOUND )
include_directories(${CPPUNIT_INCLUDE_DIRS})

set(LIBS ${LIBS}
    ${CPPUNIT_LIBRARIES}
    ${Boost_LIBRARIES}
    ${RLOG_LIBRARIES}
    ${LIBSVM_LIBRARIES}
    ${JACK_LIBRARIES}
    ${JACKCPP_LIBRARIES}
    ${ITPP_LIBRARIES})

#################
# cppunit tests #
#################

set(SOURCE_DIR
    ${CMAKE_SOURCE_DIR}/src)

set(INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/include
    ${SOURCE_DIR})
include_directories(${INCLUDE_DIR})

set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)
set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

set(MFCC_FILE OFF)

configure_file(${SOURCE_DIR}/config.h.cmake config.h)
configure_file(testconfig.h.cmake testconfig.h)

add_definitions(`pkg-config --cflags jack` `itpp-config --cflags`)
#add_definitions(-DPLOT)

macro(add_unit_test)
    foreach(TEST ${ARGV})
        message(STATUS "  found test: ${TEST}")
        get_filename_component(TestName ${TEST} NAME_WE)
        add_executable(${TestName} testRunner.cpp ${TEST})
        target_link_libraries(${TestName} ${LIBS})
        add_test(NAME ${TestName} COMMAND ${TestName})
        message(STATUS "* added test: ${TestName}")
    endforeach(TEST)
endmacro(add_unit_test)

option(ENABLE_LIB_TEST "Compile libraries tests" FALSE)
if (ENABLE_LIB_TEST OR ENABLE_ALL_TESTS)
    message(STATUS "libraries tests enabled")
    file(GLOB LIB_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "lib/*Test.cpp")
    add_unit_test(${LIB_TEST_SRCS})
else()
    message(STATUS "skipping libraries tests")
endif()

option(ENABLE_CORE_TEST "Compile core tests" FALSE)
if (ENABLE_CORE_TEST OR ENABLE_ALL_TESTS)
    message(STATUS "core tests enabled")

    add_executable(JackRingBufferTest core/JackRingBufferTest.cpp testRunner.cpp)
    target_link_libraries(JackRingBufferTest ${LIBS})
    add_test(NAME JackRingBuffer COMMAND JackRingBufferTest)
    message(STATUS "* added test: core/JackRingBufferTest.cpp")

    add_executable(RingBufferReadTest core/RingBufferReadTest.cpp testRunner.cpp ${SOURCE_DIR}/jack/ringbufferread.cpp utils/testUtils.cpp)
    target_link_libraries(RingBufferReadTest ${LIBS})    
    add_test(NAME RingBufferRead COMMAND RingBufferReadTest)
    message(STATUS "* added test: core/RingBufferReadTest.cpp")

    add_executable(utilsTest core/utilsTest.cpp testRunner.cpp ${SOURCE_DIR}/utils/utils.cpp)
    target_link_libraries(utilsTest ${LIBS})
    add_test(NAME utils COMMAND utilsTest)
    message(STATUS "* added test: core/utilsTest.cpp")

    add_executable(ProcessorTest
      testRunner.cpp
      processor/ProcessorTest.cpp
      utils/testUtils.cpp
      ${SOURCE_DIR}/processor/processor.cpp
      ${SOURCE_DIR}/features/feature.cpp
      ${SOURCE_DIR}/features/zcr.cpp
      ${SOURCE_DIR}/features/energy.cpp
      ${SOURCE_DIR}/features/ass.cpp
      ${SOURCE_DIR}/features/srf.cpp
      ${SOURCE_DIR}/features/hr.cpp
      ${SOURCE_DIR}/features/mfcc.cpp
      ${SOURCE_DIR}/features/melfb.cpp
      ${SOURCE_DIR}/utils/utils.cpp
      ${SOURCE_DIR}/utils/execpath.cpp)
    target_link_libraries(ProcessorTest ${LIBS})
    add_test(NAME processor COMMAND ProcessorTest)
    message(STATUS "* added test: processor/ProcessorTest")

    add_executable(ScaleTest
      testRunner.cpp
      model/ScaleTest.cpp
      ${SOURCE_DIR}/model/range.h
      utils/testUtils.cpp)
    target_link_libraries(ScaleTest ${LIBS})
    add_test(NAME scale COMMAND ScaleTest)
    message(STATUS "* added test: model/ScaleTest")
else()
    message(STATUS "skipping core tests")
endif()

option(ENABLE_FEATURE_TEST "Compile features tests" FALSE)
if (ENABLE_FEATURE_TEST OR ENABLE_ALL_TESTS)
    message(STATUS "features tests enabled")

    option(ENABLE_REGRESSION_TEST "Enable features regression tests" OFF)
    if (ENABLE_REGRESSION_TEST)
        message(STATUS "features regression tests enabled")
    endif()

    set(TEST_FEATURES
      testRunner.cpp
      features/FeatureTester.cpp
      utils/testUtils.cpp
      ${SOURCE_DIR}/features/feature.cpp
      ${SOURCE_DIR}/utils/utils.cpp)

    add_executable(ZcrTest
      features/ZcrTest.cpp
      ${SOURCE_DIR}/features/zcr.cpp
      ${TEST_FEATURES})
    target_link_libraries(ZcrTest ${LIBS})
    add_test(NAME zcr COMMAND ZcrTest)
    message(STATUS "* added test: features/ZcrTest")

    add_executable(EnergyTest
      features/EnergyTest.cpp
      ${SOURCE_DIR}/features/energy.cpp
      ${TEST_FEATURES})
    target_link_libraries(EnergyTest ${LIBS})
    add_test(NAME energy COMMAND EnergyTest)
    message(STATUS "* added test: features/EnergyTest")

    add_executable(AssTest
      features/AssTest.cpp
      ${SOURCE_DIR}/features/ass.cpp
      ${TEST_FEATURES})
    target_link_libraries(AssTest ${LIBS})
    add_test(NAME ass COMMAND AssTest)
    message(STATUS "* added test: features/AssTest")

    add_executable(SrfTest
      features/SrfTest.cpp
      ${SOURCE_DIR}/features/srf.cpp
      ${TEST_FEATURES})
    target_link_libraries(SrfTest ${LIBS})
    add_test(NAME srf COMMAND SrfTest)
    message(STATUS "* added test: features/SrfTest")

    add_executable(HrTest
      features/HrTest.cpp
      ${SOURCE_DIR}/features/hr.cpp
      ${TEST_FEATURES})
    target_link_libraries(HrTest ${LIBS})
    add_test(NAME hr COMMAND HrTest)
    message(STATUS "* added test: features/HrTest")

    add_executable(MfccTest
      features/MfccTest.cpp
      ${SOURCE_DIR}/features/mfcc.cpp
      ${SOURCE_DIR}/features/melfb.cpp
      ${SOURCE_DIR}/utils/execpath.cpp
      ${TEST_FEATURES})
    target_link_libraries(MfccTest ${LIBS})
    add_test(NAME mfcc COMMAND MfccTest)
    message(STATUS "* added test: features/MfccTest")
else()
    message(STATUS "skipping features tests")
endif()

option(ENABLE_MATLAB_TEST "Compile matlab test tool" FALSE)
if (ENABLE_MATLAB_TEST)
    message(STATUS "matlab test tool enabled")

    add_executable(testSignal
      matlab/testSignal.cpp
      utils/testUtils.cpp
      ${SOURCE_DIR}/utils/utils.cpp)
else()
    message(STATUS "matlab test tool not enabled")
endif()
