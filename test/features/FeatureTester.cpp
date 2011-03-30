#include "FeatureTester.h"
#include "features/feature.h"
#include "../utils/testUtils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(FeatureTest);

void FeatureTest::setUp() {
    feature = setFeature();
}

void FeatureTest::tearDown() {
     delete feature;
}

static const int FEATURES = 12;

void FeatureTest::testSignal() {
    itpp::vec result = itpp::zeros(FEATURES);
    feature->extract(getSignal(), result);
    print("result", result);
}

void FeatureTest::testSilence() {
    itpp::vec result = itpp::zeros(FEATURES);
    feature->extract(getSilence(), result);
    print("result", result);
}

void FeatureTest::testRegression() {
    doRegressionTest();
}