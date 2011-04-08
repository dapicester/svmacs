#include "FeatureTester.h"
#include "features/mfcc.h"

using std::string;

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

static const int NMFCC = 24;
static const int NCOEFF = 6;

Feature* FeatureTest::setFeature() {
    return new MFCC(sampleRate, nfft, NMFCC, NCOEFF);
}

#ifdef ENABLE_REGRESSION
static const int INDEX = 6;

void testFilterBank(MFCC* mfcc, const itpp::mat& filterBank) {
    itpp::mat wts = mfcc->getFilterBank();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("rows", filterBank.rows(), wts.rows());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("cols", filterBank.cols(), wts.cols());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("size", filterBank.size(), wts.size());

    //CPPUNIT_ASSERT_EQUAL(filterBank, wts);
#if 1
    for (int r = 0; r < filterBank.rows(); r++) {
        for (int c = 0; c < filterBank.cols(); c++) {
            register string msg = "element (" + lexical_cast<string>(r) +
                                  "," + lexical_cast<string>(c) + ")";
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(msg,
                                             filterBank(r,c),
                                             wts(r,c),
                                             FeatureTest::DELTA);
        }
    }
#endif
}

void FeatureTest::doRegressionTest(const itpp::vec& expected, const itpp::vec& data) const {
    testFilterBank(dynamic_cast<MFCC*>(feature), filterBank);
#if 0
    for (int i = 0; i < NCOEFF; i++) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected[INDEX + i], data[INDEX + i], DELTA);
    }
#endif
}

#endif
