cmake_minimum_required(VERSION 2.8)

message (STATUS "Tests")
enable_testing()

set(CMAKE_VERBOSE_MAKEFILE OFF)

# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################
# dependencies #
################

include_directories("${PROJECT_SOURCE_DIR}/lib")
link_directories("${PROJECT_SOURCE_DIR}/lib")
set(JackCpp_LIBRARIES "jackcpp")

find_package(CppUnit REQUIRED)
if ( NOT CPPUNIT_FOUND )
  message(FATAL_ERROR "Package CppUnit required, but not found!")
endif( NOT CPPUNIT_FOUND )
include_directories(${CPPUNIT_INCLUDE_DIRS})

find_package(LibSVM REQUIRED)
if ( NOT LIBSVM_FOUND )
  message(FATAL_ERROR "Package LibSVM required, but not found!")
endif( NOT LIBSVM_FOUND )
include_directories(${LIBSVM_INCLUDE_DIRS})

find_package( Boost 1.46.0 COMPONENTS thread REQUIRED )
if ( NOT Boost_FOUND )
    message(FATAL_ERROR "Boost Signals library required, but not found!")
endif (NOT Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS})

#################
# cppunit tests #
#################

set(SOURCE_DIR
    ${CMAKE_SOURCE_DIR}/src)

set(INCLUDE_DIR 
    ${CMAKE_SOURCE_DIR}/include 
    ${SOURCE_DIR})
include_directories(${INCLUDE_DIR})

add_definitions(`pkg-config --cflags jack` `itpp-config --cflags`)
#add_definitions(-DPLOT)

set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/lib)
link_directories(${LIBRARY_DIR})
link_libraries(cppunit rlog itpp svm jackcpp jack rt pthread ${Boost_LIBRARIES})

set(ENABLE_CORE_TEST true)
set(ENABLE_FEATURE_TEST true)

#file(GLOB UNITTESTS_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "core/*Test.cpp")
#foreach(TEST ${UNITTESTS_SRCS})
#  message(STATUS "* added test: ${TEST}")
#  get_filename_component(TestName ${TEST} NAME_WE)
#  add_executable(${TestName} testRunner.cpp ${TEST})
#  target_link_libraries(${TestName} cppunit itpp)
#  add_test(NAME ${TestName} COMMAND ${TestName})
#endforeach(TEST)

if (ENABLE_CORE_TEST)
    add_executable(CaseTest core/CaseTest.cpp testRunner.cpp)
    add_test(NAME Case COMMAND CaseTest)
    message(STATUS "* added test: core/CaseTest")
    
    add_executable(FixtureTest core/FixtureTest.cpp testRunner.cpp)
    add_test(NAME Fixture COMMAND FixtureTest)
    message(STATUS "* added test: core/FixtureTest")
    
    add_executable(libitppTest core/libitppTest.cpp testRunner.cpp utils/testUtils.cpp)
    add_test(NAME libitpp COMMAND libitppTest)
    message(STATUS "* added test: core/libitppTest.cpp")
    
    add_executable(libsvmTest core/libsvmTest.cpp testRunner.cpp)
    add_test(NAME libsvm COMMAND libsvmTest)
    message(STATUS "* added test: core/libsvmTest.cpp")

    add_executable(signalsTest core/signalsTest.cpp testRunner.cpp)
    add_test(NAME signals COMMAND signalsTest)
    message(STATUS "* added test: core/signalsTest.cpp")
    
    add_executable(JackRingBufferTest core/JackRingBufferTest.cpp testRunner.cpp)
    add_test(NAME JackRingBuffer COMMAND JackRingBufferTest)
    message(STATUS "* added test: core/JackRingBufferTest.cpp")
    
    add_executable(RingBufferReadTest core/RingBufferReadTest.cpp testRunner.cpp ${SOURCE_DIR}/jack/ringbufferread.cpp utils/testUtils.cpp)
    add_test(NAME RingBufferRead COMMAND RingBufferReadTest)
    message(STATUS "* added test: core/RingBufferReadTest.cpp")

    add_executable(utilsTest core/utilsTest.cpp testRunner.cpp ${SOURCE_DIR}/utils/utils.cpp)
    add_test(NAME utils COMMAND utilsTest)
    message(STATUS "* added test: core/utilsTest.cpp")
else()
    message(STATUS "skipping core tests")
endif()

if (ENABLE_FEATURE_TEST)
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
    add_test(NAME zcr COMMAND ZcrTest)
    message(STATUS "* added test: features/ZcrTest")

    add_executable(EnergyTest 
      features/EnergyTest.cpp
      ${SOURCE_DIR}/features/energy.cpp
      ${TEST_FEATURES})
    add_test(NAME energy COMMAND EnergyTest)
    message(STATUS "* added test: features/EnergyTest")

    add_executable(AssTest 
      features/AssTest.cpp
      ${SOURCE_DIR}/features/ass.cpp
      ${TEST_FEATURES})
    add_test(NAME ass COMMAND AssTest)
    message(STATUS "* added test: features/AssTest")

    add_executable(SrfTest 
      features/SrfTest.cpp
      ${SOURCE_DIR}/features/srf.cpp
      ${TEST_FEATURES})
    add_test(NAME srf COMMAND SrfTest)
    message(STATUS "* added test: features/SrfTest")

    add_executable(HrTest 
      features/HrTest.cpp
      ${SOURCE_DIR}/features/hr.cpp
      ${TEST_FEATURES})
    add_test(NAME hr COMMAND HrTest)
    message(STATUS "* added test: features/HrTest")

    add_executable(MfccTest 
      features/MfccTest.cpp
      ${SOURCE_DIR}/features/mfcc.cpp
      ${TEST_FEATURES})
    add_test(NAME mfcc COMMAND MfccTest)
    message(STATUS "* added test: features/MfccTest")
else()
    message(STATUS "skipping features tests")
endif()

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
  ${SOURCE_DIR}/utils/utils.cpp)
add_test(NAME processor COMMAND ProcessorTest)
message(STATUS "* added test: processor/ProcessorTest")

add_executable(ScaleTest
  testRunner.cpp
  model/ScaleTest.cpp
  ${SOURCE_DIR}/model/range.h
  utils/testUtils.cpp)
add_test(NAME scale COMMAND ScaleTest)
message(STATUS "* added test: model/ScaleTest")
