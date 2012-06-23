message (STATUS "Feature tests")

find_package(Boost 1.49.0 COMPONENTS filesystem system unit_test_framework REQUIRED)
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

add_executable(ZcrTest ZcrTest.cpp ${src}/zcr.cpp ${src}/feature.cpp)
target_link_libraries(ZcrTest ${LIBS})
add_test(NAME features/ZcrTest COMMAND ZcrTest)

add_executable(EnergyTest EnergyTest.cpp ${src}/energy.cpp ${src}/feature.cpp)
target_link_libraries(EnergyTest ${LIBS})
add_test(NAME features/EnergyTest COMMAND EnergyTest)

add_executable(AssTest AssTest.cpp ${src}/ass.cpp ${src}/feature.cpp)
target_link_libraries(AssTest ${LIBS})
add_test(NAME features/AssTest COMMAND AssTest)

add_executable(SrfTest SrfTest.cpp ${src}/srf.cpp ${src}/feature.cpp)
target_link_libraries(SrfTest ${LIBS})
add_test(NAME features/SrfTest COMMAND SrfTest)

add_executable(HrTest HrTest.cpp ${src}/hr.cpp ${src}/feature.cpp)
target_link_libraries(HrTest ${LIBS})
add_test(NAME features/HrTest COMMAND HrTest)

add_executable(MfccTest MfccTest.cpp ${src}/mfcc.cpp ${src}/melfb.cpp ${src}/feature.cpp ${SOURCE_DIR}/utils/execpath.cpp)
target_link_libraries(MfccTest ${LIBS} ${RLOG_LIBRARIES})
add_test(NAME features/MfccTest COMMAND MfccTest)

