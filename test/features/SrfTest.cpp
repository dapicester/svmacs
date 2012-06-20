#define BOOST_TEST_MODULE SrfTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/srf.h"

BOOST_FIXTURE_TEST_CASE(srf_test, test::Fixture) {
    svmacs::SRF feature(sampleRate);
    doTest(feature, silence);
    doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
 const int INDEX = 4;
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    BOOST_CHECK_CLOSE(expected[INDEX], data[INDEX], DELTA);
}
} /* namespace test */
#endif
