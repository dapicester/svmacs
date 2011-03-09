#ifndef FAILTEST_H
#define	FAILTEST_H

#include <cppunit/extensions/HelperMacros.h>

class FailTest : public CPPUNIT_NS::TestCase {
    
    CPPUNIT_TEST_SUITE(FailTest);

    CPPUNIT_TEST(testSuccessMethod);
    CPPUNIT_TEST_FAIL(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

private:
    void testSuccessMethod();
    void testFailedMethod();
};

#endif	/* FAILTEST_H */

