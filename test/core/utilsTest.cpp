#include "utilsTest.h"
#include "utils/utils.h"

#include <itpp/base/vec.h>
using itpp::vec;
using itpp::ivec;

CPPUNIT_TEST_SUITE_REGISTRATION(utilsTest);

static const int size = 5;
static const vec input = "0 -1 2 0 4";

void utilsTest::testFlipud() {
    vec output = flipud(input);
    vec expected = "4 0 2 -1 0";
    CPPUNIT_ASSERT_EQUAL(expected, output);
}

void utilsTest::testNumel() {
    int output = numel(input);
    CPPUNIT_ASSERT_EQUAL(size, output);
}

void utilsTest::testFind() {
    ivec output = find(input);
    ivec expected = "1 2 4";
    CPPUNIT_ASSERT_EQUAL(expected, output);
}

void utilsTest::testDiff() {
    vec output = diff(input);
    vec expected = "-1 3 -2 4";
    CPPUNIT_ASSERT_EQUAL(expected, output);
}

void utilsTest::testMaxima() {
    ivec output = maxima(input);
    ivec expected = "0 2 4";
    CPPUNIT_ASSERT_EQUAL(expected, output);
}

void utilsTest::testLinvec() {
    vec output = linvec(0, 10);
    vec expected = "0 1 2 3 4 5 6 7 8 9 10";
    CPPUNIT_ASSERT_EQUAL(expected, output);
}
