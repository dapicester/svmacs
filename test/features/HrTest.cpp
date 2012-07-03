#define BOOST_TEST_MODULE HrTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/hr.h"

/// @class svmacs::HR
/// @test Test feature extraction.
BOOST_FIXTURE_TEST_CASE(hr_test, test::Fixture) {
    svmacs::HR feature(sampleRate);
    doTest(feature, silence);
    doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
const int INDEX = 5;
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    BOOST_CHECK_CLOSE(expected[INDEX], data[INDEX], DELTA);
}
} /* namespace test */
#endif
