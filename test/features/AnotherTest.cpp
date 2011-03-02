#include "AnotherTest.h"
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION( AnotherTest );

void AnotherTest::setUp() {
  std::cout << "AssTest::setUp" << std::endl;
}
void AnotherTest::tearDown() {
  std::cout << "AssTest::tearDown" << std::endl;
}

void AnotherTest::runTest() {
  std::cout << "AssTest::failing" << std::endl;
  CPPUNIT_ASSERT(false);
}
