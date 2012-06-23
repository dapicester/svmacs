#define BOOST_TEST_MODULE JackRingBufferTest
#include <boost/test/unit_test.hpp>

#include <jackringbuffer.hpp>

BOOST_AUTO_TEST_CASE(ringbuffer) {
    const size_t SIZE = 20;
    JackCpp::RingBuffer<int> buffer(SIZE);
    BOOST_CHECK_EQUAL(SIZE, buffer.length());
    BOOST_CHECK( buffer.getWriteSpace() >= buffer.length());
    BOOST_CHECK_EQUAL(0, buffer.getReadSpace());
    
    // test data
    const size_t N = 10;
    int array[N];
    for (int i = 1; i <= N; i++) array[i] = i;
    
    // write
    buffer.write(array, N);
    BOOST_CHECK( buffer.getWriteSpace() >= (buffer.length() - N));
    BOOST_CHECK_EQUAL(N, (int) buffer.getReadSpace());
    
    //read
    int readSize = buffer.getReadSpace();
    for (int i = 0 ; buffer.getReadSpace() != 0; i++){
        BOOST_CHECK_EQUAL(readSize - i, (int) buffer.getReadSpace());
        
        int readValue;
        buffer.read(readValue);
        
        BOOST_CHECK_EQUAL(array[i], readValue);
        BOOST_CHECK_EQUAL(readSize - i - 1, (int) buffer.getReadSpace());
    }
    BOOST_CHECK_EQUAL(0, (int) buffer.getReadSpace());
}
