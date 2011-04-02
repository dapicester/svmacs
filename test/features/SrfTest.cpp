#include "FeatureTester.h"
#include "features/srf.h"

Feature* FeatureTest::setFeature() {
    return new SRF(sampleRate);
}

static const int INDEX = 4;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_EQUAL(expected[INDEX], data[INDEX]);
}
