#include "AssTest.h"
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION( AssTest );

void AssTest::setUp() {
  std::cout << "AssTest::setUp" << std::endl;
}
void AssTest::tearDown() {
  std::cout << "AssTest::tearDown" << std::endl;
}

void AssTest::runTest() {
  std::cout << "AssTest::runTest" << std::endl;

  //  CPPUNIT_ASSERT( 10 == 10 );
  //  CPPUNIT_ASSERT( !(1 == 2) );
}
