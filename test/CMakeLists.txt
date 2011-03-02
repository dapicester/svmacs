cmake_minimum_required(VERSION 2.8)

enable_testing()

# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################
# dependencies #
################

find_package(CppUnit REQUIRED)
if ( NOT CPPUNIT_FOUND )
  message(FATAL_ERROR "Package CppUnit required, but not found!")
endif( NOT CPPUNIT_FOUND )
include_directories(${CPPUNIT_INCLUDE_DIRS})

set(LIBS ${LIBS} ${CPPUNIT_LIBRARIES})

#################
# cppunit tests #
#################

file(GLOB UNITTESTS_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "features/*Test.cpp" )
# add_executable(UnitTester testRunner.cpp ${UNITTESTS_SRCS})
# target_link_libraries(UnitTester cppunit itpp)
foreach(TEST ${UNITTESTS_SRCS})
  get_filename_component(TestName ${TEST} NAME_WE)
  message(STATUS "* adding test: ${TestName}")
  add_executable(${TestName} testRunner.cpp ${TEST})
  target_link_libraries(${TestName} cppunit itpp)
  add_test(NAME ${TestName} COMMAND ${TestName})
endforeach(TEST)

#############
# OLD TESTS #
#############

set(ENABLE_OLD_TEST FALSE)

if (ENABLE_OLD_TEST)
    message(STATUS "Enabling old tests")
    set(SOURCE_DIR
	${CMAKE_SOURCE_DIR}/src)

    set(INCLUDE_DIR 
	${CMAKE_SOURCE_DIR}/include 
	${SOURCE_DIR})
    include_directories(${INCLUDE_DIR})

    add_definitions(`pkg-config --cflags jack` `itpp-config --cflags`)
    #add_definitions(-DPLOT)
    set(LIBRARY_DIR
	${CMAKE_SOURCE_DIR}/lib)
    link_directories(${LIBRARY_DIR})
    link_libraries(itpp rlog cppunit)

    set(CMAKE_VERBOSE_MAKEFILE ON)

    add_executable(test-fail testfail.cpp)
    add_executable(test-itpp testitpp.cpp)
    add_executable(test-utils testutils.cpp)
    add_executable(test-ringbuffer testringbuffer.cpp)
    target_link_libraries(test-ringbuffer jack pthread rt jackcpp)
    # add_executable(test-ringbufferread testringbufferread.cpp)
    # target_link_libraries(test-ringbufferread jack pthread rt jackcpp)


    add_executable(test-zcr 
	old/testzcr.cpp 
	${SOURCE_DIR}/features/zcr.cpp 
	${SOURCE_DIR}/features/feature.cpp)
    add_executable(test-energy 
	old/testenergy.cpp 
	${SOURCE_DIR}/features/energy.cpp 
	${SOURCE_DIR}/features/feature.cpp)
    add_executable(test-ass 
	old/testass.cpp 
	${SOURCE_DIR}/features/ass.cpp 
	${SOURCE_DIR}/features/feature.cpp)
    add_executable(test-srf
	old/testsrf.cpp 
	${SOURCE_DIR}/features/srf.cpp 
	${SOURCE_DIR}/features/feature.cpp)
    add_executable(test-hr 
	old/testhr.cpp 
	${SOURCE_DIR}/features/hr.cpp 
	${SOURCE_DIR}/features/feature.cpp)
    add_executable(test-mfcc 
	old/testmfcc.cpp 
	${SOURCE_DIR}/features/mfcc.cpp 
	${SOURCE_DIR}/features/feature.cpp)
    add_executable(test-all-features old/test_features.cpp
	${SOURCE_DIR}/features/zcr.cpp 
	${SOURCE_DIR}/features/energy.cpp
	${SOURCE_DIR}/features/ass.cpp 
	${SOURCE_DIR}/features/srf.cpp
	${SOURCE_DIR}/features/hr.cpp 
	${SOURCE_DIR}/features/mfcc.cpp 
	${SOURCE_DIR}/features/feature.cpp)

    # add_executable(test-model testmodel.cpp ${FEATURES})
    # add_executable(test-libsvm testlibsvm.cpp)
    # target_link_libraries(test-libsvm svm)

    add_test(NAME fail COMMAND test-fail)
    add_test(NAME itpp COMMAND test-itpp)
    add_test(NAME utils COMMAND test-utils)
    # add_test(NAME ringbuffer COMMAND test-ringbuffer)
    # add_test(NAME ringbufferread COMMAND test-ringbufferread)

    add_test(NAME zcr COMMAND test-zcr)
    add_test(NAME energy COMMAND test-energy)
    add_test(NAME ass COMMAND test-ass)
    add_test(NAME srf COMMAND test-srf)
    add_test(NAME hr COMMAND test-hr)
    add_test(NAME mfcc COMMAND test-mfcc)
    add_test(NAME all COMMAND test-all-features)

    # add_test(07-test-model bin/test-model)
    # add_test(08-test-libsvm bin/test-libsvm)
else()
    message(STATUS "Skipping old tests")
endif(ENABLE_OLD_TEST)