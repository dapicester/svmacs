set(INCLUDE_DIR 
    ../lib 
    ../src/jack 
    ../src/features
    ../src/utils 
)

include_directories(${INCLUDE_DIR})

add_definitions(-ggdb `pkg-config --cflags jack` `itpp-config --cflags`)
add_definitions(-DDEBUG)
#add_definitions(-DPLOT)

link_directories(${INCLUDE_DIR})
link_libraries(jack pthread rt itpp fftw3 lapack blas rlog jackcpp)

set(RING_BUFFER
    ../src/jack/ringbufferread.h
    ../src/jack/ringbufferread.cpp
)

set(FEATURES
    testfeatures.h
    ../src/features/zcr.h
    ../src/features/zcr.cpp
    ../src/features/energy.h
    ../src/features/energy.cpp
    ../src/features/ass.h
    ../src/features/ass.cpp
)

set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(test-fail testfail.cpp)
add_executable(test-utils testutils.cpp)
add_executable(test-ringbuffer testringbuffer.cpp)
add_executable(test-ringbufferread testringbufferread.cpp ${RING_BUFFER})
add_executable(test-zcr testzcr.cpp ${FEATURES})
add_executable(test-energy testenergy.cpp ${FEATURES})
add_executable(test-ass testass.cpp ${FEATURES})

enable_testing()
#add_test(00-fail ./bin/test-fail)
add_test(01-test-zcr bin/test-zcr)
add_test(02-test-energy bin/test-energy)
add_test(03-test-ass bin/test-ass)
