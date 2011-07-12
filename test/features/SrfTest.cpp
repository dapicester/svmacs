#include "FeatureTester.h"
#include "features/srf.h"

Feature* FeatureTest::setFeature() {
    return new SRF(sampleRate);
}

#ifdef ENABLE_REGRESSION_TEST
static const int INDEX = 4;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[INDEX], data[INDEX], DELTA);
}
#endif
