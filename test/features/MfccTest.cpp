#include "FeatureTester.h"
#include <features/mfcc.h>

static const int NFFT = 128*2;
static const int NMFCC = 24; 
static const int NCOEFF = 6;

features::Feature*
FeatureTest::setFeature() {
    return new features::MFCC(SAMPLE_RATE, NFFT, NMFCC, NCOEFF);
}
