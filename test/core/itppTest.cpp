#include "itppTest.h"
#include <iostream>
#include <itpp/itbase.h>

CPPUNIT_TEST_SUITE_REGISTRATION(itppTest);

void
itppTest::testMatrix() {
    itpp::mat A = "1 2 3; 4 5 6; 7 8 9"; 
    itpp::mat B = "1; 2; 3";
 
    // matrix product
    itpp::mat C = A*B; 
    // hermitian transposition
    itpp::mat D = B.hermitian_transpose() * A; 
}

void
itppTest::testVector() {
    itpp::vec v = itpp::linspace(0, 10, 10+1); 
    itpp::vec u = itpp::linspace(1, 10, 10); 
}

void 
itppTest::testEquals() {
    itpp::mat a = "1 2; 3 4";
    itpp::mat b = "1 0; 3 4";
    itpp::mat c = "1 2; 3 4";
    
    CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( a == b) );
    CPPUNIT_ASSERT_ASSERTION_PASS( CPPUNIT_ASSERT( a == c) );
}