message (STATUS "Core tests")

find_package(Boost 1.46.0 COMPONENTS system unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()
add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/libjackcpp ${JACK_INCLUDE_DIRS})
list(APPEND LIBS jackcpp-static ${JACK_LIBRARIES})

include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

include_directories(${RLOG_INCLUDE_DIRS})
list(APPEND LIBS ${RLOG_LIBRARIES})

add_unit_test(NAME JackRingBufferTest TAG core
    SOURCES JackRingBufferTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${JACK_LIBRARIES} jackcpp-static)

add_unit_test(NAME RingBufferReadTest TAG core
    SOURCES RingBufferReadTest.cpp ${SOURCE_DIR}/jack/ringbufferread.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${JACK_LIBRARIES})

add_unit_test(NAME UtilsTest TAG core
    SOURCES utilsTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${ITPP_LIBRARIES})

set(SRCS
    ${SOURCE_DIR}/processor/processor.cpp
    ${SOURCE_DIR}/features/feature.cpp
    ${SOURCE_DIR}/features/zcr.cpp
    ${SOURCE_DIR}/features/energy.cpp
    ${SOURCE_DIR}/features/ass.cpp
    ${SOURCE_DIR}/features/srf.cpp
    ${SOURCE_DIR}/features/hr.cpp
    ${SOURCE_DIR}/features/mfcc.cpp
    ${SOURCE_DIR}/features/melfb.cpp
)
add_unit_test(NAME ProcessorTest TAG core
    SOURCES ProcessorTest.cpp ${SRCS}
    LINK_LIBRARIES ${LIBS})

add_unit_test(NAME ScaleTest TAG core
    SOURCES ScaleTest.cpp
    LINK_LIBRARIES ${Boost_LIBRARIES} ${ITPP_LIBRARIES})

