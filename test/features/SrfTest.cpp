#include "FeatureTester.h"
#include <features/srf.h>

features::Feature*
FeatureTest::setFeature() {
    return new features::SRF(SAMPLE_RATE);
}
