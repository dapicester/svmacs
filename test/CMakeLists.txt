set(INCLUDE_DIR 
    ../lib 
    ../src/jack 
    ../src/features
    ../src/utils 
)

include_directories(${INCLUDE_DIR})

#find_package(LAPACK REQUIRED)
#find_package(BLAS REQUIRED)

add_definitions(-ggdb `pkg-config --cflags jack` `itpp-config --cflags --static --libs`)
#add_definitions(-DDEBUG)
#add_definitions(-DPLOT)

link_directories(${INCLUDE_DIR})
link_directories(/usr/lib/gcc/i486-linux-gnu/4.2/)
link_libraries(jack pthread rt itpp fftw3 lapack blas rlog jackcpp)

set(RING_BUFFER
    ../src/jack/ringbufferread.h
    ../src/jack/ringbufferread.cpp
)

set(ZCR testfeatures.h
    ../src/features/zcr.h
    ../src/features/zcr.cpp
)

set(ENERGY testfeatures.h
    ../src/features/energy.h
    ../src/features/energy.cpp
)

set(ASS testfeatures.h
    ../src/features/ass.h
    ../src/features/ass.cpp
) 

set(SRF testfeatures.h
    ../src/features/srf.h
    ../src/features/srf.cpp
)

set(HR testfeatures.h
    ../src/features/hr.h
    ../src/features/hr.cpp
)

set(MFCC testfeatures.h
    ../src/features/mfcc.h
    ../src/features/mfcc.cpp
)

set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(test-fail testfail.cpp)
add_executable(test-itpp testitpp.cpp)
add_executable(test-utils testutils.cpp)
add_executable(test-ringbuffer testringbuffer.cpp)
add_executable(test-ringbufferread testringbufferread.cpp ${RING_BUFFER})
add_executable(test-zcr testzcr.cpp ${ZCR})
add_executable(test-energy testenergy.cpp ${ENERGY})
add_executable(test-ass testass.cpp ${ASS})
add_executable(test-srf testsrf.cpp ${SRF})
add_executable(test-hr testhr.cpp ${HR})
add_executable(test-mfcc testmfcc.cpp ${MFCC})

enable_testing()
#add_test(00-fail ./bin/test-fail)
#add_test(00-itpp ./bin/test-itpp)
add_test(01-test-zcr bin/test-zcr)
add_test(02-test-energy bin/test-energy)
add_test(03-test-ass bin/test-ass)
add_test(04-test-srf bin/test-srf)
add_test(04-test-hr bin/test-hr)
