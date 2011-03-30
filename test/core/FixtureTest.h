#ifndef FIXTURETEST_H
#define	FIXTURETEST_H

#include <cppunit/extensions/HelperMacros.h>

class FixtureTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FixtureTest);
    CPPUNIT_TEST(testSuccessMethod);
    CPPUNIT_TEST_FAIL(testFailedMethod);
    CPPUNIT_TEST_SUITE_END();
    
public:
    void setUp();
    void tearDown();

private:
    void testSuccessMethod();
    void testFailedMethod();
};

#endif	/* FIXTURETEST_H */

