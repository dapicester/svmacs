#include "ProcessorTest.h"
#include "processor/processor.h"
#include "utils/testUtils.h"

#include <itpp/itbase.h>
using namespace itpp;

#define RLOG_COMPONENT "processor"
#include <rlog/rlog.h>

/// Default sample rate
static const int SAMPLE_RATE = 1024;      
    
CPPUNIT_TEST_SUITE_REGISTRATION( ProcessorTest );
        
void ProcessorTest::setUp() {
    processor = new Processor(SAMPLE_RATE);
}

void ProcessorTest::tearDown() {
    delete processor;
}

void ProcessorTest::testSilence() {
    vec silence = getSilence();
    vec result = processor->process(silence);
    print("feature vector", result);
}

void ProcessorTest::testSignal() {
    vec signal = getSignal();
    vec result = processor->process(signal);
    print("feature vector", result);
}

static const std::string TEST_FILE = "/home/paolo/NetBeansProjects/svmacs2"
                                     "/test/processor/test_signal.it";

void ProcessorTest::testOnline() {
    it_file file(TEST_FILE);
    vec signal;
    file >> Name("test_signal") >> signal;
    CPPUNIT_ASSERT(signal.length() > 0);
    
    int length = 1 * SAMPLE_RATE; // 1 second
    for (int i = 0; i + length < signal.length() ; i += length) {
        rDebug("reading samples [%d+%d]", i, length);
        vec frame = signal.mid(i, length);
        vec features = processor->process(frame);
        rDebug("feature vector:\n%s", itpp::to_str(features).c_str());
    }
}
