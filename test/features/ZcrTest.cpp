#include "FeatureTester.h"
#include "features/zcr.h"

Feature* FeatureTest::setFeature() {
    return new ZCR(SAMPLE_RATE);
}

void FeatureTest::doRegressionTest() {
    // TODO
}
