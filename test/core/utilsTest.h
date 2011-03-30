#ifndef UTILSTEST_H
#define	UTILSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class utilsTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(utilsTest);
    CPPUNIT_TEST(testFlipud);
    CPPUNIT_TEST(testNumel);
    CPPUNIT_TEST(testFind);
    CPPUNIT_TEST(testDiff);
    CPPUNIT_TEST(testMaxima);
    CPPUNIT_TEST(testLinvec);
    CPPUNIT_TEST_SUITE_END();

private:
    void testFlipud();
    void testNumel();
    void testFind();
    void testDiff();
    void testMaxima();
    void testLinvec();
};

#endif	/* UTILSTEST_H */
