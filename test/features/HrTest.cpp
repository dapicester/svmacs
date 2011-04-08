#include "FeatureTester.h"
#include "features/hr.h"

Feature* FeatureTest::setFeature() {
    return new HR(sampleRate);
}

#ifdef ENABLE_REGRESSION
static const int INDEX = 5;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[INDEX], data[INDEX], DELTA);
}
#endif
