#ifndef CASETEST_H
#define	CASETEST_H

#include <cppunit/extensions/HelperMacros.h>

class CaseTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(CaseTest);
    CPPUNIT_TEST(testSuccessMethod);
    CPPUNIT_TEST_FAIL(testFailedMethod);
    CPPUNIT_TEST_SUITE_END();

private:
    void testSuccessMethod();
    void testFailedMethod();
};

#endif	/* FAILTEST_H */

