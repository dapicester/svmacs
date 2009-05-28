set(INCLUDE_DIR 
    ../lib 
    ../src/jack 
    ../src/features
    ../src/utils 
)

include_directories(${INCLUDE_DIR})

add_definitions(-Wall -W -ggdb `pkg-config --cflags jack` `itpp-config --cflags`)
add_definitions(-DDEBUG)

#link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${INCLUDE_DIR})
link_libraries(jack pthread rt itpp fftw3 lapack blas rlog jackcpp)

set(RING_BUFFER
    ../src/jack/ringbufferread.h
    ../src/jack/ringbufferread.cpp
)

set(FEATURES
    ../src/features/zcr.h
    ../src/features/zcr.cpp
    ../src/features/energy.h
    ../src/features/energy.cpp
    ../src/features/ass.h
    ../src/features/ass.cpp
)

add_executable(test-fail testfail.cpp)
add_executable(test-utils testutils.cpp)
add_executable(test-ringbuffer testringbuffer.cpp)
add_executable(test-ringbufferread testringbufferread.cpp ${RING_BUFFER})
add_executable(test-features testfeatures.cpp ${FEATURES})

enable_testing()
add_test(00-fail test-fail)
add_test(01-utils test-utils)
add_test(02-ringbuffer test-ringbuffer)
add_test(03-ringbufferread test-ringbufferread)
add_test(04-features test-features)

