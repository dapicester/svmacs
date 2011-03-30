#include "FeatureTester.h"
#include "features/hr.h"

Feature* FeatureTest::setFeature() {
    return new HR(SAMPLE_RATE);
}

void FeatureTest::doRegressionTest() {
    // TODO compare C++ and Matlab
}
