#ifndef ASS_TEST_H
#define ASS_TEST_H

class Feature;

#include <itpp/itbase.h>
#include <cppunit/extensions/HelperMacros.h>

typedef struct {
    itpp::vec samples;
    itpp::vec spectrum;
    itpp::vec expected;
} testData;

class FeatureTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(FeatureTest);
    CPPUNIT_TEST(testSilence);
    CPPUNIT_TEST(testSignal);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testSilence();
    void testSignal();

private:
    /** Pointer to the actual feature extractor */
    Feature* feature;

    /** Obtain a pointer to a concrete feature extractor. */
    Feature* setFeature();

    /** Extract data. */
    itpp::vec extract(const testData& input) const;

    /** Perform regression test on actual feature extractor. */
    void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const;

    double sampleRate;
    double nfft;
    testData signal;
    testData silence;
};

#endif
