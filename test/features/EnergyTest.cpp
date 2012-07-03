#define BOOST_TEST_MODULE EnergyTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/energy.h"

/// @class svmacs::Energy
/// @test Test feature extraction.
BOOST_FIXTURE_TEST_CASE(energy_test, test::Fixture) {
    svmacs::Energy feature(sampleRate);
    test::doTest(feature, silence);
    test::doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
const int INDEX = 1;
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    BOOST_CHECK_CLOSE(expected[INDEX], data[INDEX], DELTA);
}
} /* namespace test */
#endif
