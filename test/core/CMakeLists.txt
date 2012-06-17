message (STATUS "Core tests")

find_package(Boost 1.49.0 COMPONENTS filesystem system unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()
add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/libjackcpp ${JACK_INCLUDE_DIRS})
list(APPEND LIBS jackcpp ${JACK_LIBRARIES})

include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

include_directories(${RLOG_INCLUDE_DIRS})
list(APPEND LIBS ${RLOG_LIBRARIES})

add_executable(JackRingBufferTest JackRingBufferTest.cpp)
target_link_libraries(JackRingBufferTest ${LIBS})
add_test(NAME core/JackRingBufferTest COMMAND JackRingBufferTest)

add_executable(RingBufferReadTest RingBufferReadTest.cpp ${SOURCE_DIR}/jack/ringbufferread.cpp)
target_link_libraries(RingBufferReadTest ${LIBS})
add_test(NAME core/RingBufferReadTest COMMAND RingBufferReadTest)

add_executable(UtilsTest utilsTest.cpp ${SOURCE_DIR}/utils/utils.cpp)
target_link_libraries(UtilsTest ${LIBS})
add_test(NAME core/UtilsTest COMMAND UtilsTest)

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
    ${SOURCE_DIR}/utils/utils.cpp
    ${SOURCE_DIR}/utils/execpath.cpp # TODO: rimuovere
)
add_executable(ProcessorTest ProcessorTest.cpp ${SRCS})
target_link_libraries(ProcessorTest ${LIBS})
add_test(NAME core/ProcessorTest COMMAND ProcessorTest)

add_executable(ScaleTest ScaleTest.cpp)
target_link_libraries(ScaleTest ${LIBS})
add_test(NAME core/ScaleTest COMMAND ScaleTest)

