#include "FailTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(FailTest);

void FailTest::testSuccessMethod() {
    CPPUNIT_ASSERT(true);
}

void FailTest::testFailedMethod() {
    CPPUNIT_ASSERT(false);
}

