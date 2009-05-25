include_directories(../lib ../src/jack ../src/utils)

add_definitions(-Wall -W -ggdb `pkg-config --cflags jack` `itpp-config --cflags`)

#link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(../lib ../src/jack)
link_libraries(jack pthread rt itpp fftw3 lapack blas rlog jackcpp)

set(RING_BUFFER
	../src/jack/ringbufferread.h
	../src/jack/ringbufferread.cpp
)

add_executable(testutils testutils.cpp)
add_executable(testringbuffer testringbuffer.cpp)
add_executable(testringbufferread testringbufferread.cpp ${RING_BUFFER})
