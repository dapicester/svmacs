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

#define BOOST_TEST_MODULE libsvmTest
#include <boost/test/unit_test.hpp>

#include "testconfig.h"
#include <libsvm/svm.h>

#include <iostream>
using std::cout;
using std::endl;

void
modelInfo(const char* fileName) {
    const svm_model* model = svm_load_model(fileName);
    BOOST_CHECK(model != NULL);

    // model info
    cout << "filename: " << fileName << endl;
    cout << "svm_type: " << svm_get_svm_type(model) << endl;
    cout << "nr_class: " << svm_get_nr_class(model) << endl;
}

/// Test load m1 file.
BOOST_AUTO_TEST_CASE(m1_test) {
    modelInfo(DATA_DIR "/m1");
}

/// Test load m2 file.
BOOST_AUTO_TEST_CASE(model_test) {
    modelInfo(DATA_DIR "/model");
}

