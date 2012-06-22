cmake_minimum_required(VERSION 2.8)

message (STATUS "Library: jackcpp")

find_package(JACK REQUIRED)
if(NOT JACK_FOUND)
    message(FATAL_ERROR "JACK not found")
endif()
include_directories(${JACK_INCLUDE_DIRS})

set(jackcpp_SRCS jackaudioio.cpp jackblockingaudioio.cpp)

add_library(jackcpp SHARED ${jackcpp_SRCS})
target_link_libraries(jackcpp ${JACK_LIBRARIES})

add_library(jackcpp-static STATIC ${jackcpp_SRCS})
