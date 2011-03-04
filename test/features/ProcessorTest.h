#ifndef PROCESSORTEST_H
#define	PROCESSORTEST_H

#include <features/processor.h>
#include <cppunit/extensions/HelperMacros.h>

class ProcessorTest : public CPPUNIT_NS::TestFixture {
  
  CPPUNIT_TEST_SUITE( ProcessorTest );
  CPPUNIT_TEST( testSilence );
  CPPUNIT_TEST( testSignal );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
  
  protected:   
    void testSilence();
    void testSignal();
  
  private:
    /// Default sample rate
    static const int SAMPLE_RATE = 1024;  
    
    features::Processor* processor;
    
    itpp::vec silence;
    itpp::vec signal;
};

#endif	/* PROCESSORTEST_H */

