#include "JackRingBufferTest.h"

#include <jackringbuffer.hpp>

#define P(X) std::cout << #X << X << std::endl; 

CPPUNIT_TEST_SUITE_REGISTRATION(JackRingBufferTest);

void JackRingBufferTest::doTest() {
    JackCpp::RingBuffer<int> buffer(20);
    CPPUNIT_ASSERT_EQUAL(20, (int) buffer.length());
    CPPUNIT_ASSERT( buffer.getWriteSpace() >= buffer.length());
    CPPUNIT_ASSERT_EQUAL(0, (int) buffer.getReadSpace());
    
    // test data
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // write
    buffer.write(array, 10);
    CPPUNIT_ASSERT( buffer.getWriteSpace() >= (buffer.length() - 10));
    CPPUNIT_ASSERT_EQUAL(10, (int) buffer.getReadSpace());
    
    //read
    int readSize = buffer.getReadSpace();
    for (int i = 0 ; buffer.getReadSpace() != 0; i++){
        CPPUNIT_ASSERT_EQUAL(readSize - i, (int) buffer.getReadSpace());
        
        int readValue;
        buffer.read(readValue);
        
        CPPUNIT_ASSERT_EQUAL(array[i], readValue);
        CPPUNIT_ASSERT_EQUAL(readSize - i - 1, (int) buffer.getReadSpace());
    }
    CPPUNIT_ASSERT_EQUAL(0, (int) buffer.getReadSpace());
}