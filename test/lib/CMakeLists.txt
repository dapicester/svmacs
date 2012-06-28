message (STATUS "Libraries tests")

find_package(Boost 1.46.0 COMPONENTS filesystem system thread unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()
add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

include_directories(${LIBSVM_INCLUDE_DIRS})
list(APPEND LIBS ${LIBSVM_LIBRARIES})

include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/libjackcpp ${JACK_INCLUDE_DIRS})
list(APPEND LIBS jackcpp-static ${JACK_LIBRARIES})

add_unit_test(NAME itppTest TAG lib
    SOURCES libitppTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${ITPP_LIBRARIES})

add_unit_test(NAME svmTest TAG lib
    SOURCES libsvmTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${LIBSVM_LIBRARIES})

add_unit_test(NAME signalsTest TAG lib
    SOURCES signalsTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES})

add_unit_test(NAME JackRingBufferTest TAG lib
    SOURCES JackRingBufferTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${JACK_LIBRARIES} jackcpp-static)

