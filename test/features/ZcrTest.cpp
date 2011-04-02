#include "FeatureTester.h"
#include "features/zcr.h"

Feature* FeatureTest::setFeature() {
    return new ZCR(sampleRate);
}

static const int INDEX = 0;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_EQUAL(expected[INDEX], data[INDEX]);
}
