#ifndef ASS_TEST_H
#define ASS_TEST_H

#include <features/feature.h>
#include <cppunit/extensions/HelperMacros.h>

class FeatureTest : public CPPUNIT_NS::TestFixture {
  
  CPPUNIT_TEST_SUITE( FeatureTest );
  CPPUNIT_TEST( testSilence );
  CPPUNIT_TEST( testSignal );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    FeatureTest();
    ~FeatureTest();
    void setUp();
    void tearDown();
  
  protected:   
    void testSilence();
    void testSignal();
  
  private:
    /// Default sample rate
    static const int SAMPLE_RATE = 1024;  
    
    features::Feature* feature;
    itpp::vec silence;
    itpp::vec signal;
      
    /// Obtain a pointer to a concrete feature extractor
    features::Feature* setFeature();
};

#endif
