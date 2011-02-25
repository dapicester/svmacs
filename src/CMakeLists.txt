# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################
# dependencies #
################

find_package(Qt4 REQUIRED)
if ( NOT QT4_FOUND )
  message(FATAL_ERROR "Package Qt4 required, but not found!")
endif( NOT QT4_FOUND )
include(${QT_USE_FILE})

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

set(EXTRA_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
set(EXTRA_LIBRARIES "jackcpp")
include_directories(${EXTRA_INCLUDE_DIRS})
link_directories("${PROJECT_SOURCE_DIR}/lib")

set(LIBS ${LIBS} ${RLOG_LIBRARIES} ${LIBSVM_LIBRARIES} ${JACK_LIBRARIES} ${ITPP_LIBRARIES} ${EXTRA_LIBRARIES})
message(STATUS "Linking against following libraries: ${LIBS}")

#add_definitions(`itpp-config --cflags`)
add_definitions(-Wall -W -pipe)
add_definitions(-fbounds-check)

if (DEBUG)
  set(CMAKE_BUILD_TYPE Debug)
  message(STATUS "Enabling debugging symbols")
  add_definitions(-DENABLE_DEBUG)
else()
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Release build")
endif()

###########
# headers #
###########

set(svmacs_HDRS
	features/processor.h
	features/feature.h
	features/zcr.h
	features/energy.h
	features/ass.h 
	features/srf.h 
	features/hr.h 
	features/mfcc.h
	model/classifier.h
	model/event.h
	model/svmclassifier.h
	jack/jackclient.h
	jack/ringbufferread.h
	cli/svmaccli.h
	gui/svmacgui.h
)

###########
# sources #
###########

set(svmacs_SRCS
	features/processor.cpp
	features/zcr.cpp
	features/energy.cpp
	features/ass.cpp
	features/srf.cpp 
	features/hr.cpp 
	features/mfcc.cpp
	model/event.cpp
	model/svmclassifier.cpp
	jack/jackclient.cpp
	jack/ringbufferread.cpp
	cli/svmaccli.cpp
	gui/svmacgui.cpp
	main.cpp 
)

# For a large number of source files you can create it in a simpler way
# using file() function:
# file(GLOB hellworld_SOURCES *.cpp)

### qt4 ui
set(svmacs_UIS gui/svmacgui.ui)
qt4_wrap_ui(svmacs_UIS_H ${svmacs_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

### qt4 moc
set(svmacs_MOCS 
	jack/jackclient.h
	gui/svmacgui.h
)
qt4_wrap_cpp(svmacs_MOCS_SRC ${svmacs_MOCS})

### qt4 resources
set (svmacs_RCCS application.qrc)
qt4_add_resources(svmacs_RCCS_SRC ${svmacs_RCCS})

##########
# binary #
##########

# executable
add_executable(svmacs ${svmacs_SRCS} ${svmacs_HDRS} ${svmacs_UIS_H} ${svmacs_MOCS_SRC} ${svmacs_RCCS_SRC})
# link
target_link_libraries(svmacs ${QT_LIBRARIES} ${LIBS})

# output dir
set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

add_custom_command(
	TARGET svmacs
	POST_BUILD
	COMMAND cp src/model/m1 src/model/model ${BIN_DIR}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMENT "Copying model files"
)

#################
# documentation #
#################

# check if doxygen is even installed
find_package(Doxygen)
if (DOXYGEN_FOUND STREQUAL "NO")
    message(FATAL_ERROR "Doxygen not found!")
endif (DOXYGEN_FOUND STREQUAL "NO")

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
