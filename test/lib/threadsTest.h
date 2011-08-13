#ifndef THREADSTEST_H
#define	THREADSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ThreadsTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(ThreadsTest);
    CPPUNIT_TEST(doTest);
    CPPUNIT_TEST_SUITE_END();

private:
    void doTest();
};

#endif	/* THREADSTEST_H */

