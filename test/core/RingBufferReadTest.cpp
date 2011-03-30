#include "RingBufferReadTest.h"

#include "jack/ringbufferread.h"
#include "../utils/testUtils.h"

#define P(X) std::cout << #X << X << std::endl; 

CPPUNIT_TEST_SUITE_REGISTRATION(RingBufferReadTest);

void RingBufferReadTest::doTest() {
    // test data
    double array[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0};
    int arraySize = 10;
    
    int bufferSize = 2 * arraySize + 1;
    RingBufferRead buffer(bufferSize); // grande abbastanza
    CPPUNIT_ASSERT_EQUAL( bufferSize, (int) buffer.length() );
    CPPUNIT_ASSERT( buffer.getWriteSpace() >= buffer.length() );
    CPPUNIT_ASSERT_EQUAL(0, (int) buffer.getReadSpace());

    // write
    buffer.write(array, arraySize);
    CPPUNIT_ASSERT( buffer.getWriteSpace() >= (buffer.length() - arraySize));
    CPPUNIT_ASSERT_EQUAL(arraySize, (int) buffer.getReadSpace());
    
    //read
    int readSize = buffer.getReadSpace();
    for (int i = 0 ; buffer.getReadSpace() != 0; i++){
        CPPUNIT_ASSERT_EQUAL(readSize - i, (int) buffer.getReadSpace());
        
        double peekValue;
        buffer.peek(peekValue);
        CPPUNIT_ASSERT_EQUAL(array[i], peekValue);
        CPPUNIT_ASSERT_EQUAL(readSize - i, (int) buffer.getReadSpace());
        
        double readValue;
        buffer.read(readValue);
        CPPUNIT_ASSERT_EQUAL(array[i], readValue);
        CPPUNIT_ASSERT_EQUAL(readSize - i - 1, (int) buffer.getReadSpace());
    }
    CPPUNIT_ASSERT_EQUAL(0, (int) buffer.getReadSpace());
}

void RingBufferReadTest::testReadAndPeek() {
    const int length = 4;
    const int overlap = 2;
    
    double data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int data_len = 10;
    
    RingBufferRead buffer(2 * length + 1);
    buffer.write(data, data_len);
    
    double expected[][4] = {
        { 0, 1, 2, 3 },
        { 2, 3, 4, 5 },
        { 4, 5, 6, 7 },
        { 6, 7, 8, 9 }
    };
    
    double frame[length];
    for (int i = 0; (int) buffer.getReadSpace() >= length; i++) {
        buffer.read(frame, length - overlap);
        buffer.peek(frame + overlap, overlap);
        CPPUNIT_ASSERT(equals(expected[i], frame, length));
    }
}
