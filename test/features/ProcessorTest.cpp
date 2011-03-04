#include "ProcessorTest.h"
#include <utils/testUtils.h>

CPPUNIT_TEST_SUITE_REGISTRATION( ProcessorTest );
        
void        
ProcessorTest::setUp() {
    processor = new features::Processor(SAMPLE_RATE);
    silence = getSilence();
    signal = getSignal();
}

void 
ProcessorTest::tearDown() {
    delete processor;
}

void
ProcessorTest::testSilence() {
    itpp::vec result = processor->process(silence);
    print(result);
}

void
ProcessorTest::testSignal() {
    itpp::vec result = processor->process(signal);
    print(result);
}
