message(STATUS "Executable: svmacs")

macro_build_info()

# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################
# dependencies #
################

include_directories(${PROJECT_SOURCE_DIR}/libjackcpp)
list(APPEND LIBS jackcpp-static)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS})
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS})
    message(STATUS "OpenMP found, multithreading enabled")
endif()

find_package(Boost 1.46.0 COMPONENTS filesystem signals system program_options REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost libraries not found.")
endif()
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

find_package(RLog REQUIRED)
if(NOT RLOG_FOUND)
    message(FATAL_ERROR "RLog not found.")
endif()
include_directories(${RLOG_INCLUDE_DIRS})
list(APPEND LIBS ${RLOG_LIBRARIES})

find_package(LibSVM REQUIRED)
if(NOT LIBSVM_FOUND)
    message(FATAL_ERROR "LibSVM not found.")
endif()
include_directories(${LIBSVM_INCLUDE_DIRS})
list(APPEND LIBS ${LIBSVM_LIBRARIES})

find_package(JACK REQUIRED)
if(NOT JACK_FOUND)
    message(FATAL_ERROR "JACK not found.")
endif()
include_directories(${JACK_INCLUDE_DIRS})
list(APPEND LIBS ${JACK_LIBRARIES})

find_package(ITPP REQUIRED)
if(NOT ITPP_FOUND)
    message(FATAL_ERROR "IT++ not found.")
endif()
include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

find_package(Qt4 4.4 COMPONENTS QtCore QtGui)
if(NOT QT4_FOUND)
    message(WARNING "Qt4 not found, disabling the GUI")
    set(ENABLE_GUI OFF)
else()
    set(ENABLE_GUI ON)
    include(${QT_USE_FILE})
    add_definitions(-DQT_NO_KEYWORDS -DQT_CONSOLE)
    list(APPEND LIBS ${QT_LIBRARIES})
endif()

message(STATUS "Linking against following libraries:")
foreach(LIB ${LIBS})
    message(STATUS "  ${LIB}")
endforeach()

add_definitions(-Wall -W -pipe)

option(ENABLE_LOG "Enable logging" OFF)

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
    classifier/svmclassifier.cpp
    jack/jackclient.cpp
    engine/engine.cpp
    cli/svmaccli.cpp
    main.cpp
)

if(ENABLE_GUI)
    set(svmacs_SRCS ${svmacs_SRCS} gui/svmacgui1.cpp gui/svmacgui2.cpp)

    # Qt UI
    set(svmacs_UIS gui/svmacgui.ui)
    qt4_wrap_ui(svmacs_UIS_H ${svmacs_UIS})

    # Qt MOC
    set(svmacs_MOCS gui/svmacgui.h)
    qt4_wrap_cpp(svmacs_MOCS_SRC ${svmacs_MOCS})

    # Qt resources
    set(svmacs_RCCS application.qrc)
    qt4_add_resources(svmacs_RCCS_SRC ${svmacs_RCCS})
endif()

##########
#  files #
##########

set(svmacs_FILES
    ${PROJECT_SOURCE_DIR}/data/m1
    ${PROJECT_SOURCE_DIR}/data/model
    ${PROJECT_SOURCE_DIR}/data/melfb.it
    ${PROJECT_SOURCE_DIR}/data/config
)

set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/${INSTALL_DATA})

set(CONFIG_FILE ${DATA_DIR}/config)
set(DFILE ${DATA_DIR}/model)
set(CFILE ${DATA_DIR}/m1)

option(USE_MFCC_FILE "Load MFCC filter bank matrix from file" OFF)
if(USE_MFCC_FILE)
    set(MFCC_FILE ${DATA_DIR}/melfb.it)
    message(STATUS "Using MFCC filter bank matrix file")
endif()

configure_file(version.h.in version.h)
configure_file(config.h.in config.h)
configure_file(${PROJECT_SOURCE_DIR}/data/config.in ${PROJECT_SOURCE_DIR}/data/config)

##########
# binary #
##########

# output dir
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(svmacs ${svmacs_SRCS} ${svmacs_UIS_H} ${svmacs_MOCS_SRC} ${svmacs_RCCS_SRC})
target_link_libraries(svmacs ${LIBS})

install(TARGETS svmacs RUNTIME DESTINATION ${INSTALL_BIN})
install(FILES ${svmacs_FILES} DESTINATION ${INSTALL_DATA})

#################
# documentation #
#################

option(BUILD_DOC "Build documentation" OFF)
if(BUILD_DOC)
    message(STATUS "Generating documentation")
    include(MacroAddDoxygen)
    add_doxygen()
endif()
