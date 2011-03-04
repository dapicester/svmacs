#ifndef MODELTEST_H
#define	MODELTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ScaleTest : public CPPUNIT_NS::TestCase {
    
    CPPUNIT_TEST_SUITE(ScaleTest);
    CPPUNIT_TEST(testScaleData);
    CPPUNIT_TEST_SUITE_END();

private:
    void testScaleData();
};

#endif	/* MODELTEST_H */

