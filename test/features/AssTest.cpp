#include "FeatureTester.h"
#include <features/ass.h>

features::Feature*
FeatureTest::setFeature() {
    return new features::ASS(SAMPLE_RATE);
}
