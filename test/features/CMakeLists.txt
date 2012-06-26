message (STATUS "Feature tests")

find_package(Boost 1.49.0 COMPONENTS unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()
add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

cmake_dependent_option(ENABLE_REGRESSION_TEST "Enable comparison between Matlab code and C++ code" OFF "ENABLE_TESTING" OFF)
if(ENABLE_REGRESSION_TEST)
    add_definitions(-DENABLE_REGRESSION_TEST)
endif()

set(src ${SOURCE_DIR}/features)

add_unit_test(NAME ZcrTest TAG features
    SOURCES ZcrTest.cpp ${src}/zcr.cpp ${src}/feature.cpp
    LINK_LIBRARIES ${LIBS})

add_unit_test(NAME EnergyTest TAG features
    SOURCES EnergyTest.cpp ${src}/energy.cpp ${src}/feature.cpp
    LINK_LIBRARIES ${LIBS})

add_unit_test(NAME AssTest TAG features
    SOURCES AssTest.cpp ${src}/ass.cpp ${src}/feature.cpp
    LINK_LIBRARIES ${LIBS})

add_unit_test(NAME SrfTest TAG features
    SOURCES SrfTest.cpp ${src}/srf.cpp ${src}/feature.cpp
    LINK_LIBRARIES ${LIBS})

add_unit_test(NAME HrTest TAG features
    SOURCES HrTest.cpp ${src}/hr.cpp ${src}/feature.cpp
    LINK_LIBRARIES ${LIBS})

add_unit_test(NAME MfccTest TAG features
    SOURCES MfccTest.cpp ${src}/mfcc.cpp ${src}/melfb.cpp ${src}/feature.cpp
    LINK_LIBRARIES ${LIBS})

