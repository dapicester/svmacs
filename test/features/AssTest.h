#ifndef ASS_TEST_H
#define ASS_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class AssTest : public CppUnit::TestFixture {
  
  CPPUNIT_TEST_SUITE( AssTest );
  CPPUNIT_TEST ( runTest );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
  
  //protected:   
    void runTest();
  
};

#endif
