#include "FeatureTester.h"
#include "features/ass.h"

Feature* FeatureTest::setFeature() {
    return new ASS(SAMPLE_RATE);
}

void FeatureTest::doRegressionTest() {
    // TODO compare C++ and Matlab
}
