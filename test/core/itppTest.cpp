#include "itppTest.h"

#include <iostream>

#define PRINT(X) std::cout << #X << ": " << X << std::endl;

#include <itpp/itbase.h>

CPPUNIT_TEST_SUITE_REGISTRATION(itppTest);

void
itppTest::test_a() {
    itpp::mat A = "1 2 3; 4 5 6; 7 8 9"; 
    PRINT(A);
    
    itpp::mat B = "1; 2; 3";
    PRINT(B);
    
    itpp::mat C = A*B; 
    PRINT(C);
    
    itpp::mat D = B.hermitian_transpose() * A; 
    PRINT(D);
}

void
itppTest::test_b() {
    itpp::vec v = itpp::linspace(0, 10, 10+1); 
    PRINT(v);
    
    itpp::vec u = itpp::linspace(1, 10, 10); 
    PRINT(u);
}