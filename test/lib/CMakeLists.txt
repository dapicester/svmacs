message (STATUS "Libraries tests")

find_package(Boost 1.49.0 COMPONENTS filesystem system thread unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()
add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBS ${Boost_LIBRARIES})

include_directories(${LIBSVM_INCLUDE_DIRS})
list(APPEND LIBS ${LIBSVM_LIBRARIES})

include_directories(${ITPP_INCLUDE_DIRS})
list(APPEND LIBS ${ITPP_LIBRARIES})

add_executable(itppTest libitppTest.cpp)
target_link_libraries(itppTest ${LIBS})
add_test(NAME itppTest COMMAND itppTest)

add_executable(svmTest libsvmTest.cpp)
target_link_libraries(svmTest ${LIBS})
add_test(NAME svmTest COMMAND svmTest)

add_executable(signalsTest signalsTest.cpp)
target_link_libraries(signalsTest ${LIBS})
add_test(NAME signalsTest COMMAND signalsTest)

