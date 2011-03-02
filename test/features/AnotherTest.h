#ifndef ANOTHER_TEST_H
#define ANOTHER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class AnotherTest : public CppUnit::TestFixture {
  
  CPPUNIT_TEST_SUITE( AnotherTest );
  CPPUNIT_TEST ( runTest );
  CPPUNIT_TEST_SUITE_END();
  
  public:
    void setUp();
    void tearDown();
  
  //protected:   
    void runTest();
  
};

#endif
