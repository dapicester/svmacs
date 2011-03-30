#include "CaseTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CaseTest);

void CaseTest::testSuccessMethod() {
    CPPUNIT_ASSERT(true);
}

void CaseTest::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

