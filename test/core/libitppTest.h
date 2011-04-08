#ifndef LIBITPPTEST_H
#define	LIBITPPTEST_H

#include <cppunit/extensions/HelperMacros.h>

class libitppTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(libitppTest);
    CPPUNIT_TEST(testMatrix);
    CPPUNIT_TEST(testVector);
    CPPUNIT_TEST(testEquals);
    CPPUNIT_TEST(testWriteFile);
    CPPUNIT_TEST(testReadFile);
    //CPPUNIT_TEST(testRead);
    CPPUNIT_TEST_SUITE_END();

private:
    void testMatrix();
    void testVector();
    void testEquals();
    void testWriteFile();
    void testReadFile();
    void testRead();
};


#endif	/* ITPPTEST_H */
