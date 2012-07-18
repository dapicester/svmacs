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

#define BOOST_TEST_MODULE SrfTest
#include <boost/test/unit_test.hpp>

#include "Fixture.h"
#include "features/srf.h"

/// @class svmacs::SRF
/// @test Test feature extraction.
BOOST_FIXTURE_TEST_CASE(srf_test, test::Fixture) {
    svmacs::SRF feature(sampleRate);
    doTest(feature, silence);
    doTest(feature, signal);
}

#ifdef ENABLE_REGRESSION_TEST
namespace test {
 const int INDEX = 4;
void doRegressionTest(const itpp::vec& expected, const itpp::vec& data) {
    BOOST_CHECK_CLOSE(expected[INDEX], data[INDEX], DELTA);
}
} /* namespace test */
#endif
