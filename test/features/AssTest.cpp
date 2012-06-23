#define BOOST_TEST_MODULE AssTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/ass.h"

BOOST_FIXTURE_TEST_CASE(ass_silence, test::Fixture) {
    svmacs::ASS feature(sampleRate);
    test::doTest(feature, silence);
    test::doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
const int INDEX = 2;
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    BOOST_CHECK_CLOSE(expected[INDEX], data[INDEX], DELTA);
    BOOST_CHECK_CLOSE(expected[INDEX + 1], data[INDEX + 1], DELTA);
}
} /* namespace test */
#endif
