#include "FeatureTester.h"
#include "features/srf.h"

Feature* FeatureTest::setFeature() {
    return new SRF(SAMPLE_RATE);
}

void FeatureTest::doRegressionTest() {
    // TODO compare C++ and Matlab
}
