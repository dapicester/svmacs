#ifndef ITPPTEST_H
#define	ITPPTEST_H

#include <cppunit/extensions/HelperMacros.h>

class itppTest : public CPPUNIT_NS::TestCase {
    
    CPPUNIT_TEST_SUITE(itppTest);

    CPPUNIT_TEST(testMatrix);
    CPPUNIT_TEST(testVector);
    CPPUNIT_TEST(testEquals);

    CPPUNIT_TEST_SUITE_END();

private:
    void testMatrix();
    void testVector();
    void testEquals();
};


#endif	/* ITPPTEST_H */

