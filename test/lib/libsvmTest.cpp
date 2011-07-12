#include "testconfig.h"
#include "libsvmTest.h"

#include <libsvm/svm.h>

using std::string;
using std::cout;
using std::endl;

CPPUNIT_TEST_SUITE_REGISTRATION(libsvmTest);

void libsvmTest::testModelNovelty() {
    modelInfo(string(DATA_DIR) + "/m1");
}

void libsvmTest::testModelClassification() {
    modelInfo(string(DATA_DIR) + "/model");
}

void libsvmTest::modelInfo(const std::string fileName) {
    const svm_model* model = svm_load_model(fileName.c_str());
    CPPUNIT_ASSERT (model != NULL);
    
    // model info
    cout << endl;
    cout << "svm_type: " << svm_get_svm_type(model) << endl;
    cout << "nr_class: " << svm_get_nr_class(model) << endl;
}

