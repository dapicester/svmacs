#define BOOST_TEST_MODULE RingBufferReadTest
#include <boost/test/unit_test.hpp>

#include "jack/ringbufferread.h"
using svmacs::RingBufferRead;

//#include "../utils/testUtils.h"

#define P(X) std::cout << #X << X << std::endl; 

BOOST_AUTO_TEST_CASE(buffer_test) {
    // test data
    double array[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0};
    const size_t arraySize = 10;
    
    const size_t bufferSize = 2 * arraySize + 1;
    RingBufferRead buffer(bufferSize);

    BOOST_CHECK_EQUAL(bufferSize, buffer.length());
    BOOST_CHECK(buffer.getWriteSpace() >= buffer.length());
    BOOST_CHECK_EQUAL(0, buffer.getReadSpace());

    // write
    buffer.write(array, arraySize); // FIXME: cannot use const double*
    BOOST_CHECK(buffer.getWriteSpace() >= (buffer.length() - arraySize));
    BOOST_CHECK_EQUAL(arraySize, buffer.getReadSpace());
    
    // read
    size_t readSize = buffer.getReadSpace();
    for (int i = 0 ; buffer.getReadSpace() != 0; i++){
        BOOST_CHECK_EQUAL(readSize - i, buffer.getReadSpace());
        
        double peekValue;
        buffer.peek(peekValue);
        BOOST_CHECK_EQUAL(array[i], peekValue);
        BOOST_CHECK_EQUAL(readSize - i, buffer.getReadSpace());
        
        double readValue;
        buffer.read(readValue);
        BOOST_CHECK_EQUAL(array[i], readValue);
        BOOST_CHECK_EQUAL(readSize - i - 1, buffer.getReadSpace());
    }
    BOOST_CHECK_EQUAL(0, buffer.getReadSpace());
}

BOOST_AUTO_TEST_CASE(peek_test) {
    const int length = 4;
    const int overlap = 2;
    
    double data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int data_len = 10;
    
    RingBufferRead buffer(2 * length + 1);
    buffer.write(data, data_len); // FIXME: cannot use const double*
    
    const double expected[][4] = {
        { 0, 1, 2, 3 },
        { 2, 3, 4, 5 },
        { 4, 5, 6, 7 },
        { 6, 7, 8, 9 }
    };
    
    double frame[length];
    for (int i = 0; buffer.getReadSpace() >= length; i++) {
        buffer.read(frame, length - overlap);
        buffer.peek(frame + overlap, overlap);
        BOOST_CHECK_EQUAL_COLLECTIONS(expected[i], expected[i] + length, frame, frame + length);
    }
}

