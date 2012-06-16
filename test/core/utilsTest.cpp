#define BOOST_TEST_MODULE UtilsTest
#include <boost/test/unit_test.hpp>

#include "utils/utils.h"

#include <itpp/base/vec.h>
using itpp::vec;
using itpp::ivec;

const int size = 5;
const vec input = "0 -1 2 0 4";

BOOST_AUTO_TEST_CASE(flipud_test) {
    vec output = flipud(input);
    const vec expected = "4 0 2 -1 0";
    BOOST_CHECK_EQUAL(expected, output);
}

BOOST_AUTO_TEST_CASE(numel_test) {
    int output = numel(input);
    BOOST_CHECK_EQUAL(size, output);
}

BOOST_AUTO_TEST_CASE(find_test) {
    ivec output = find(input);
    const ivec expected = "1 2 4";
    BOOST_CHECK_EQUAL(expected, output);
}

BOOST_AUTO_TEST_CASE(diff_test) {
    vec output = diff(input);
    const vec expected = "-1 3 -2 4";
    BOOST_CHECK_EQUAL(expected, output);
}

BOOST_AUTO_TEST_CASE(maxima_test) {
    ivec output = maxima(input);
    const ivec expected = "0 2 4";
    BOOST_CHECK_EQUAL(expected, output);
}

BOOST_AUTO_TEST_CASE(linvec_test) {
    vec output = linvec(0, 10);
    const vec expected = "0 1 2 3 4 5 6 7 8 9 10";
    BOOST_CHECK_EQUAL(expected, output);
}

