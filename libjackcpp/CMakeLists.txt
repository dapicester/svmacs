cmake_minimum_required(VERSION 2.8)

message (STATUS "Library: jackcpp")

################
# dependencies #
################

find_package(JACK REQUIRED)
if ( NOT JACK_FOUND )
    message(FATAL_ERROR "Package JACK required, but not found!")
endif( NOT JACK_FOUND )
include_directories(${JACK_INCLUDE_DIRS})

set(LIBS ${JACK_LIBRARIES})
set(CMAKE_BUILD_TYPE Release)

###########
# sources #
###########

set(jackcpp_SRCS
    jackaudioio.cpp
    jackblockingaudioio.cpp
)

##########
# output #
##########

add_library(jackcpp SHARED ${jackcpp_SRCS})
set_target_properties(jackcpp PROPERTIES LINKER_LANGUAGE CXX)
