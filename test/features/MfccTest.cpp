#include "FeatureTester.h"
#include "features/mfcc.h"

static const int NMFCC = 24;
static const int NCOEFF = 6;

Feature* FeatureTest::setFeature() {
    return new MFCC(sampleRate, nfft, NMFCC, NCOEFF);
}

#ifdef ENABLE_REGRESSION
static const int INDEX = 6;

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    for (int i = 0; i < NCOEFF; i++) {
        CPPUNIT_ASSERT_EQUAL(expected[INDEX + i], data[INDEX + i]);
    }
}
#endif
