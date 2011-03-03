#include "FeatureTester.h"
#include <features/hr.h>

features::Feature*
FeatureTest::setFeature() {
    return new features::HR(SAMPLE_RATE);
}
