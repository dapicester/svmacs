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

#define BOOST_TEST_MODULE ScaleTest
#include <boost/test/unit_test.hpp>

#include "model/range.h"
using namespace itpp;
using namespace svmacs;

const double DELTA = 1e-9;

/// @fn itpp::mat svmacs::scaleData(const itpp::mat&, const itpp::mat&)
/// @test Test scaling in a matrix.
/// @fn itpp::vec svmacs::scaleData(const itpp::vec&, const itpp::mat&)
/// @test Test scaling in a vector.
BOOST_AUTO_TEST_CASE(scaleData_test) {
    const mat input =
    "0.2500    0.5000    0.7500    1.0000    1.2500    1.5000    1.7500    2.0000;"
    "2.2500    2.0000    1.7500    1.5000    1.2500    1.0000    0.7500    0.5000;"
    "0.5000    1.0000    1.5000    2.0000    2.5000    3.0000    3.5000    4.0000;"
    "4.5000    4.0000    3.5000    3.0000    2.5000    2.0000    1.5000    1.0000;"
    "1.0000    2.0000    3.0000    4.0000    5.0000    6.0000    7.0000    8.0000;"
    "9.0000    8.0000    7.0000    6.0000    5.0000    4.0000    3.0000    2.0000;"
    "2.0000    4.0000    6.0000    8.0000   10.0000   12.0000   14.0000   16.0000;"
   "18.0000   16.0000   14.0000   12.0000   10.0000    8.0000    6.0000    4.0000";

   const mat range =
   " 0     0     0     0     0     0     0     0;"
   "10    10    10    10    10    10    10    10";

   const mat expected =
   "-0.9500   -0.9000   -0.8500   -0.8000   -0.7500   -0.7000   -0.6500   -0.6000;"
   "-0.5500   -0.6000   -0.6500   -0.7000   -0.7500   -0.8000   -0.8500   -0.9000;"
   "-0.9000   -0.8000   -0.7000   -0.6000   -0.5000   -0.4000   -0.3000   -0.2000;"
   "-0.1000   -0.2000   -0.3000   -0.4000   -0.5000   -0.6000   -0.7000   -0.8000;"
   "-0.8000   -0.6000   -0.4000   -0.2000         0    0.2000    0.4000    0.6000;"
   " 0.8000    0.6000    0.4000    0.2000         0   -0.2000   -0.4000   -0.6000;"
   "-0.6000   -0.2000    0.2000    0.6000    1.0000    1.4000    1.8000    2.2000;"
   " 2.6000    2.2000    1.8000    1.4000    1.0000    0.6000    0.2000   -0.2000";

   // scale vector
   for (int i = 0; i < input.rows(); i++) {
        vec vscaled = scaleData(input.get_row(i), range);
        const vec& vexpected = expected.get_row(i);
        for (int j = 0; j < vscaled.length(); j++) {
            BOOST_CHECK_CLOSE(vexpected[j], vscaled[j], DELTA);
        }
   }

   // scale matrix
   mat scaled = scaleData(input, range);
   for (int i = 0; i < expected.size(); i++) {
       BOOST_CHECK_CLOSE(expected.get(i), scaled.get(i), DELTA);
   }
}
