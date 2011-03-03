#include "FeatureTester.h"
#include <features/energy.h>

features::Feature*
FeatureTest::setFeature() {
    return new features::Energy(SAMPLE_RATE);
}
