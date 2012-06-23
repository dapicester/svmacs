#define BOOST_TEST_MODULE ZcrTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/zcr.h"

BOOST_FIXTURE_TEST_CASE(zcr_test, test::Fixture) {
    svmacs::ZCR feature(sampleRate);
    test::doTest(feature, silence);
    test::doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
const int INDEX = 0;
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    BOOST_CHECK_CLOSE(expected[INDEX], data[INDEX], DELTA);
}
} /* namespace test */
#endif
