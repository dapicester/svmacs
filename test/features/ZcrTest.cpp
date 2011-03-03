#include "FeatureTester.h"
#include <features/zcr.h>

features::Feature*
FeatureTest::setFeature() {
    return new features::ZCR(SAMPLE_RATE);
}
