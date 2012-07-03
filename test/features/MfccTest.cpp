#define BOOST_TEST_MODULE MfccTest
#include <boost/test/unit_test.hpp>

#include "testconfig.h"
#include "Fixture.h"
#include "features/mfcc.h"

const int NUM_FILTERS = 24;
const int NUM_COEFF   = 6;

#if defined(ENABLE_REGRESSION_TEST) && defined(MFCC_FILE)
namespace test {
void testFilterBank(const svmacs::MFCC& mfcc, const itpp::mat& filterBank);
}
#endif

/// @class svmacs::MFCC
/// @test Test feature extraction.
BOOST_FIXTURE_TEST_CASE(mfcc_test, test::Fixture) {
    svmacs::MFCC feature(sampleRate, nfft, NUM_FILTERS, NUM_COEFF);
    doTest(feature, silence);
    doTest(feature, signal);
#if defined(ENABLE_REGRESSION_TEST) && defined(MFCC_FILE)
    test::testFilterBank(dynamic_cast<const svmacs::MFCC&>(feature), filterBank);
#endif
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
const int INDEX = 6;
#ifdef MFCC_FILE
void testFilterBank(const svmacs::MFCC& mfcc, const itpp::mat& filterBank) {
    const itpp::mat& wts = mfcc.getFilterBank();

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
#endif
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    for (int i = 0; i < NUM_COEFF; i++) {
        BOOST_CHECK_CLOSE(expected[INDEX + i], data[INDEX + i], DELTA);
    }
}
} /* namespace test */
#endif

#ifdef MFCC_FILE
BOOST_AUTO_TEST_CASE(melfb_file) {
    itpp::cmat wts;
    itpp::it_ifile file(MFCC_FILE);

    file >> itpp::Name("wts") >> wts;
}
#endif
