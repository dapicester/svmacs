#ifndef SIGNALSTEST_H
#define	SIGNALSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class SignalsTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(SignalsTest);
    CPPUNIT_TEST(doTest);
    CPPUNIT_TEST_SUITE_END();

private:
    void doTest();
};

#endif	/* SIGNALSTEST_H */

