#include "libitppTest.h"
#include "utils/testUtils.h"
#include "utils/path.h"

#include <iostream>
#include <itpp/itbase.h>
using namespace itpp;

CPPUNIT_TEST_SUITE_REGISTRATION(libitppTest);

#define P(X) std::cout << std::endl << #X << ": " << X << std::endl;

void libitppTest::testMatrix() {
    mat A = "1 2 3; 4 5 6; 7 8 9";
    mat B = "1; 2; 3";

    // matrix product
    mat C = A*B;
    // hermitian transposition
    mat D = B.hermitian_transpose() * A;
}

void libitppTest::testVector() {
    vec v = itpp::linspace(0, 10, 10+1);
    vec u = itpp::linspace(1, 10, 10);

    std::string us = itpp::to_str(u);
    P(us);
}

void libitppTest::testEquals() {
    mat a = "1 2; 3 4";
    mat b = "1 0; 3 4";
    mat c = "1 2; 3 4";

    CPPUNIT_ASSERT ( a == a);
    CPPUNIT_ASSERT_ASSERTION_FAIL( CPPUNIT_ASSERT( a == b) );
    CPPUNIT_ASSERT_ASSERTION_PASS( CPPUNIT_ASSERT( a == c) );
}

static const std::string FILE_NAME = PATH + "test/core/test.it";

void libitppTest::testWriteFile() {
    int i = -22;
    double d = 3.1415;
    vec v = "1 2 3 4 5";
    mat m = "1 2 3; 1 2 3";

    it_file file(FILE_NAME);
    file << Name("i") << i;
    file << Name("d") << d;
    file << Name("v") << v;
    file << Name("m") << m;
    file.close();
}

void libitppTest::testReadFile() {
    int i;
    double d;
    vec v;
    mat m;

    it_file file(FILE_NAME);
    file >> Name("i") >> i;
    file >> Name("d") >> d;
    file >> Name("v") >> v;
    file >> Name("m") >> m;

    CPPUNIT_ASSERT_EQUAL(-22, i);
    CPPUNIT_ASSERT_EQUAL(3.1415, d);
    CPPUNIT_ASSERT_EQUAL(vec("1 2 3 4 5"), v);
    CPPUNIT_ASSERT_EQUAL(mat("1 2 3; 1 2 3"), m);
}

static const std::string MATLAB_FILE = PATH + "test/matlab/prova.it";

void libitppTest::testRead() { // FIXME: bug itpp?
    double val;

    it_file file(MATLAB_FILE);
    file >> Name("prova") >> val;

}