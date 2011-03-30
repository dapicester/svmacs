#ifndef RINGBUFFERREADTEST_H
#define	RINGBUFFERREADTEST_H

#include <cppunit/extensions/HelperMacros.h>

class RingBufferReadTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(RingBufferReadTest);
    CPPUNIT_TEST(doTest);
    CPPUNIT_TEST(testReadAndPeek);
    CPPUNIT_TEST_SUITE_END();

private:
    void doTest();
    void testReadAndPeek();
};


#endif/* RINGBUFFERREADTEST_H */
