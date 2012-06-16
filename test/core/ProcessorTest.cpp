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

/// Default sample rate
const int SAMPLE_RATE = 1024;

struct Fixture {
    Fixture() : processor(SAMPLE_RATE) {
        vec silence = test::getSilence();
    }
    ~Fixture() {}
    Processor processor;
    vec silence;
    vec signal;
};

BOOST_FIXTURE_TEST_CASE(silence_test, Fixture) {
    vec result = processor.process(silence);
    //print("feature vector", result);
}

BOOST_FIXTURE_TEST_CASE(signal_test, Fixture) {
    vec result = processor.process(signal);
    //print("feature vector", result);
}

const std::string TEST_FILE = std::string(TEST_DATA_DIR) + "/test_signal.it";

BOOST_AUTO_TEST_CASE(online_test) {
    Processor processor(SAMPLE_RATE);
    vec signal;
    { // load signal from file
        it_file file(TEST_FILE);
        file >> Name("test_signal") >> signal;
        BOOST_REQUIRE(signal.length() > 0);
    }

    const int length = 1 * SAMPLE_RATE; // 1 second
    for (int i = 0; i + length < signal.length() ; i += length) {
        rDebug("reading samples [%d+%d]", i, length);
        vec frame = signal.mid(i, length);
        vec features = processor.process(frame);
        rDebug("feature vector:\n%s", to_str(features).c_str());
    }
}

