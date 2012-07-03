#define BOOST_TEST_MODULE ProcessorTest
#include <boost/test/unit_test.hpp>

#include "testconfig.h"
#include "testUtils.h"

#include "processor/processor.h"
using namespace svmacs;

#include <itpp/itbase.h>
using namespace itpp;

#define RLOG_COMPONENT "processor"
#include <rlog/rlog.h>

namespace test {

const int SAMPLE_RATE = 1024;
const int SIGNAL_LEN  = 1 * SAMPLE_RATE;

const std::string TEST_FILE = TEST_DATA_DIR "/test_signal.it";

/// ProcessorTest fixture.
struct Fixture {
    Fixture() : processor(SAMPLE_RATE) {
        silence = test::getSilence();
        vec time = test::getTime(0.0, 1.0, 0.01);
        signal = test::getSignal(time);
    }
    ~Fixture() {}
    Processor processor;
    vec silence;
    vec signal;
};

} /* namespace test */

#if 0
BOOST_AUTO_TEST_CASE(test_utils) {
    using namespace test;

    // print
    print("ciao");
    vec v = "1 2 3 4";
    print("v", v);
    mat m = "1 2;3 5";
    print("m", m);

    // getTime
    print("time1", getTime(0, 10));
    print("time2", getTime(0, 1, 0.1));

    // getSilence
    print("silence", getSilence(10));

    // getSignal
    getSignal(getTime(0, 1, 0.01), 4, 2);
}
#endif

/// @class svmacs::Processor
/// @test Test processing on a silence signal.
BOOST_FIXTURE_TEST_CASE(silence_test, test::Fixture) {
    vec result = processor.process(silence);
    test::print("feature vector", result);
}

/// @class svmacs::Processor
/// @test Test processing on a signal.
BOOST_FIXTURE_TEST_CASE(signal_test, test::Fixture) {
    vec result = processor.process(signal);
    test::print("feature vector", result);
}

/// @class svmacs::Processor
/// @test Test online processing (OLA analysis) on a recorded signal.
BOOST_AUTO_TEST_CASE(online_test) {
    using namespace test;

    Processor processor(SAMPLE_RATE);
    vec signal;
    { // load signal from file
        it_file file(TEST_FILE);
        file >> Name("test_signal") >> signal;
        BOOST_REQUIRE(signal.length() > 0);
    }

    const int length = 0.05 * SAMPLE_RATE; // 50 ms
    for (int i = 0; i + length < signal.length() ; i += length) {
        rDebug("reading samples [%d+%d]", i, length);
        vec frame = signal.mid(i, length);
        vec features = processor.process(frame);
        rDebug("feature vector:\n%s", to_str(features).c_str());
    }
}
