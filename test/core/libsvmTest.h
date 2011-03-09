#ifndef LIBSVMTEST_H
#define	LIBSVMTEST_H

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>

class libsvmTest : public CPPUNIT_NS::TestCase {
    CPPUNIT_TEST_SUITE(libsvmTest);

    CPPUNIT_TEST(testModelNovelty);
    CPPUNIT_TEST(testModelClassification);

    CPPUNIT_TEST_SUITE_END();

private:
    void testModelNovelty();
    void testModelClassification();
    
    /// modelInfo
    void modelInfo(const std::string model);
};

#endif	/* LIBSVMTEST_H */

