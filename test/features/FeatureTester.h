#ifndef ASS_TEST_H
#define ASS_TEST_H

class Feature;

#include <cppunit/extensions/HelperMacros.h>

class FeatureTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FeatureTest);
    CPPUNIT_TEST(testSilence);
    CPPUNIT_TEST(testSignal);
    CPPUNIT_TEST(testRegression);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testSilence();
    void testSignal();
    void testRegression();
    
    static const int SAMPLE_RATE = 1024;

private:
    Feature* feature;
    
    /// Obtain a pointer to a concrete feature extractor
    Feature* setFeature();
    /// Perform regression test on actual feature extractor
    void doRegressionTest();
};

#endif
