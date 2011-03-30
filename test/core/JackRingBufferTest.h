#ifndef JACKRINGBUFFERTEST_H
#define	JACKRINGBUFFERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class JackRingBufferTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(JackRingBufferTest);
    CPPUNIT_TEST(doTest);
    CPPUNIT_TEST_SUITE_END();

private:
    void doTest();
};


#endif/* JACKRINGBUFFERTEST_H */
