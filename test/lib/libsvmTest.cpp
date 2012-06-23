#define BOOST_TEST_MODULE libsvmTest
#include <boost/test/unit_test.hpp>

#include "testconfig.h"
#include <libsvm/svm.h>

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

