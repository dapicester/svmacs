cmake_minimum_required(VERSION 2.8)

message (STATUS "Executable: svmacs")

# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################
# dependencies #
################

include_directories("${PROJECT_SOURCE_DIR}/libjackcpp")

find_package( Boost 1.46.0 COMPONENTS signals program_options system filesystem REQUIRED )
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

set(LIBS ${LIBS}
    ${Boost_LIBRARIES}
    ${RLOG_LIBRARIES}
    ${LIBSVM_LIBRARIES}
    ${JACK_LIBRARIES}
    ${ITPP_LIBRARIES})
message(STATUS "Linking against following libraries:")
foreach(LIB ${LIBS})
    message(STATUS "  ${LIB}")
endforeach(LIB)

add_definitions(-Wall -W -pipe)
add_definitions(-fbounds-check)

option(DEBUG "Debug build" OFF)
option(ENABLE_LOG "Enable logging" OFF)

if (DEBUG)
    message(STATUS "Enabling debugging symbols")
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Enabling debug logging")
    set(ENABLE_LOG ON)
else()
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Release build")
endif()

option(MFCC_FILE "Load MFCC filter bank matrix from file" ON)
if (MFCC_FILE)
    message(STATUS "Using MFCC filter bank matrix file")
endif()

###########
# sources #
###########

set(svmacs_SRCS
    features/feature.cpp
    features/zcr.cpp
    features/energy.cpp
    features/ass.cpp
    features/srf.cpp
    features/hr.cpp
    features/mfcc.cpp
    features/melfb.cpp
    processor/processor.cpp
    model/event.cpp
    classifier/svmclassifier.cpp
    jack/jackclient.cpp
    jack/ringbufferread.cpp
    engine/engine.cpp
    cli/svmaccli.cpp
    utils/utils.cpp
    utils/execpath.cpp
    main.cpp
)

configure_file(version.h.cmake version.h)
configure_file(config.h.cmake config.h)

###############
# model files #
###############

set(svmacs_MODELS
    ${PROJECT_SOURCE_DIR}/data/m1
    ${PROJECT_SOURCE_DIR}/data/model
    ${PROJECT_SOURCE_DIR}/data/melfb.it
)

# For a large number of source files you can create it in a simpler way
# using file() function:
# file(GLOB hellworld_SOURCES *.cpp)

##########
# binary #
##########

# output dir
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(svmacs ${svmacs_SRCS})
target_link_libraries(svmacs jackcpp ${LIBS})

install(TARGETS svmacs DESTINATION .)
install(FILES ${svmacs_MODELS} DESTINATION .)

add_custom_command(
    TARGET svmacs
    POST_BUILD
    COMMAND cp ${svmacs_MODELS} ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Copying model files to dir ${CMAKE_BINARY_DIR} ..."
)

#################
# documentation #
#################

option(BUILD_DOC "Build documentation" OFF)
if(BUILD_DOC)
    message(STATUS "Generating documentation")

    # check if doxygen is even installed
    find_package(Doxygen)
    if (DOXYGEN_FOUND STREQUAL "NO")
        message(WARNING "Doxygen not found, skipping")
    else()
        # prepare doxygen configuration file
        #configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${PROJECT_SOURCE_DIR}/Doxyfile)

        # add doxygen as target
        add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile)

        # cleanup $build/api-doc on "make clean"
        set_property(DIRECTORY APPEND PROPERTY
                    ADDITIONAL_MAKE_CLEAN_FILES doc)

        # add doxygen as dependency to doc-target
        get_target_property(DOC_TARGET doc TYPE)
        if(NOT DOC_TARGET)
                add_custom_target(doc)
        endif()
        add_dependencies(doc doxygen)

        # install HTML API documentation and manual pages
        set(DOC_PATH "share/doc/${CPACK_PACKAGE_NAME}-${VERSION}")

        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html
                DESTINATION ${DOC_PATH}
              )

        # install man pages into packages, scope is now project root..
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/man/man3
                DESTINATION share/man/man3/
              )
    endif(DOXYGEN_FOUND STREQUAL "NO")
endif(BUILD_DOC)
