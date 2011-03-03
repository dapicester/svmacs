#ifndef ITPPTEST_H
#define	ITPPTEST_H

#include <cppunit/extensions/HelperMacros.h>

class itppTest : public CPPUNIT_NS::TestCase {
    
    CPPUNIT_TEST_SUITE(itppTest);

    CPPUNIT_TEST(test_a);
    CPPUNIT_TEST(test_b);

    CPPUNIT_TEST_SUITE_END();

public:
    void test_a();
    void test_b();
};


#endif	/* ITPPTEST_H */

