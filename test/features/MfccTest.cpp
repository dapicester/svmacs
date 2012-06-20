#define BOOST_TEST_MODULE MfccTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/mfcc.h"

BOOST_FIXTURE_TEST_CASE(mfcc_test, test::Fixture) {
    svmacs::MFCC feature(sampleRate, nfft, 24, 6);
    doTest(feature, silence);
    doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
const int INDEX = 6;
void testFilterBank(const MFCC& mfcc, const itpp::mat& filterBank) {
    itpp::mat wts = mfcc->getFilterBank();

    BOOST_CHECK_EQUAL(filterBank.rows(), wts.rows());
    BOOST_CHECK_EQUAL(filterBank.cols(), wts.cols());
    BOOST_CHECK_EQUAL(filterBank.size(), wts.size());

    /* element-wise assertion */
    for (int r = 0; r < filterBank.rows(); r++) {
        for (int c = 0; c < filterBank.cols(); c++) {
            BOOST_CHECK_CLOSE(filterBank(r,c), wts(r,c), DELTA);
        }
    }
}
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    testFilterBank(dynamic_cast<const MFCC&>(feature), filterBank);
    for (int i = 0; i < NCOEFF; i++) {
        BOOST_CHECK_CLOSE(expected[INDEX + i], data[INDEX + i], DELTA);
    }
}
} /* namespace test */
#endif
