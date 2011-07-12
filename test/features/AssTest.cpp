#include "FeatureTester.h"
#include "features/ass.h"

#include <itpp/itcomm.h>
using namespace itpp;

Feature* FeatureTest::setFeature() {
    return new ASS(sampleRate);
}

#ifdef ENABLE_REGRESSION_TEST
static const int INDEX = 2;

void FeatureTest::doRegressionTest(const vec& expected, const vec& data) const {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[INDEX], data[INDEX], DELTA);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[INDEX + 1], data[INDEX + 1], DELTA);
}

#endif
