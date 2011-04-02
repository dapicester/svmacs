#include "FeatureTester.h"
#include "features/energy.h"

Feature* FeatureTest::setFeature() {
    return new Energy(sampleRate);
}

#ifdef ENABLE_REGRESSION
static const int INDEX = 1;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    CPPUNIT_ASSERT_EQUAL(expected[INDEX], data[INDEX]);
}
#endif
