#include "FeatureTester.h"
#include "features/energy.h"

Feature* FeatureTest::setFeature() {
    return new Energy(sampleRate);
}

#ifdef ENABLE_REGRESSION_TEST
static const int INDEX = 1;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[INDEX], data[INDEX], DELTA);
}
#endif
