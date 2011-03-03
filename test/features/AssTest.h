#ifndef ASS_TEST_H
#define ASS_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class AssTest : public CPPUNIT_NS::TestFixture {
  
  CPPUNIT_TEST_SUITE( AssTest );
  CPPUNIT_TEST ( runTest );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
  
  protected:   
    void runTest();
  
};

#endif
