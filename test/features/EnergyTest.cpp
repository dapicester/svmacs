#include "FeatureTester.h"
#include "features/energy.h"

Feature* FeatureTest::setFeature() {
    return new Energy(SAMPLE_RATE);
}

void FeatureTest::doRegressionTest() {
    // TODO compare C++ and Matlab
}
