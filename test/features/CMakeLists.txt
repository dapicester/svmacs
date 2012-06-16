message (STATUS "Feature tests")

find_package(Boost 1.49.0 COMPONENTS system unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()
add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

message(WARNING "TODO: rewrite tests")
#add_executable(ZcrTest ZcrTest.cpp)
#target_link_libraries(ZcrTest ${LIBS})
#add_test(NAME ZcrTest COMMAND ZcrTest)

