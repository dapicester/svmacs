#ifndef PROCESSORTEST_H
#define	PROCESSORTEST_H

class Processor;

#include <cppunit/extensions/HelperMacros.h>

class ProcessorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ProcessorTest);
    CPPUNIT_TEST(testSilence);
    CPPUNIT_TEST(testSignal);
    CPPUNIT_TEST(testOnline);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testSilence();
    void testSignal();
    void testOnline();

private:
    Processor* processor;
};

#endif/* PROCESSORTEST_H */
