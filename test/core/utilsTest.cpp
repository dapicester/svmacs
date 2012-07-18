/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#define BOOST_TEST_MODULE UtilsTest
#include <boost/test/unit_test.hpp>

#include "utils/utils.h"
using namespace svmacs;

#include <itpp/base/vec.h>
using itpp::vec;
using itpp::ivec;

const int size = 5;
const vec input = "0 -1 2 0 4";

/// @fn itpp::Vec<T> svmacs::flipud(const itpp::Vec<T>&)
/// @test Checks that given the input "[0 -1 2 0 4]" the output is "[4 0 2 -1 0]".
BOOST_AUTO_TEST_CASE(flipud_test) {
    vec output = flipud(input);
    const vec expected = "4 0 2 -1 0";
    BOOST_CHECK_EQUAL(expected, output);
}

/// @fn itpp::ivec svmacs::find(const itpp::Vec<T>&)
/// @test Check that given the input "[0 -1 2 0 4]" the output is "[1 2 4]".
BOOST_AUTO_TEST_CASE(find_test) {
    ivec output = find(input);
    const ivec expected = "1 2 4";
    BOOST_CHECK_EQUAL(expected, output);
}

/// @fn itpp::Vec<T> svmacs::diff(const itpp::Vec<T>&)
/// @test Check that given the input "[0 -1 2 0 4]" the output is "[-1 3 -2 4]".
BOOST_AUTO_TEST_CASE(diff_test) {
    vec output = diff(input);
    const vec expected = "-1 3 -2 4";
    BOOST_CHECK_EQUAL(expected, output);
}

/// @fn itpp::ivec svmacs::maxima(const itpp::Vec<T>&)
/// @test Check that given the input "[0 -1 2 0 4]" the output is "[0 2 4]".
BOOST_AUTO_TEST_CASE(maxima_test) {
    ivec output = maxima(input);
    const ivec expected = "0 2 4";
    BOOST_CHECK_EQUAL(expected, output);
}

/// @fn itpp::Vec<T> svmacs::linvec(const T start, const T stop, const T step)
/// @test Check that given the inputs (0, 10) the output is "[0 1 2 3 4 5 6 7 8 9 10]".
BOOST_AUTO_TEST_CASE(linvec_test) {
    ivec output = linvec(0, 10);
    const ivec expected = "0 1 2 3 4 5 6 7 8 9 10";
    BOOST_CHECK_EQUAL(expected, output);
}

