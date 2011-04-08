#include "FixtureTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(FixtureTest);

#define RLOG_COMPONENT "FixtureTest"
#include <rlog/rlog.h>

void FixtureTest::setUp() {
    rInfo("setUp");
}

void FixtureTest::tearDown() {
    rInfo("tearDown");
}

void FixtureTest::testSuccessMethod() {
    rInfo("test");
    CPPUNIT_ASSERT(true);
}

void FixtureTest::testFailedMethod() {
    rInfo("test");
    CPPUNIT_ASSERT(false);
}

