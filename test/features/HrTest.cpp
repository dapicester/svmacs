#include "FeatureTester.h"
#include "features/hr.h"

Feature* FeatureTest::setFeature() {
    return new HR(sampleRate);
}

static const int INDEX = 5;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_EQUAL(expected[INDEX], data[INDEX]);
}
