#include "libsvmTest.h"

using namespace std;
#include <libsvm/svm.h>
#include <cppunit/TestAssert.h>
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(libsvmTest);

void libsvmTest::testModelNovelty() {
    modelInfo("/bin/m1");
}

void libsvmTest::testModelClassification() {
    modelInfo("/bin/model");
}

void libsvmTest::modelInfo(const std::string fileName) {
    const svm_model* model = svm_load_model(fileName.c_str());
    CPPUNIT_ASSERT (model != NULL);
    
    // model info
    cout << "svm_type: " << svm_get_svm_type(model) << endl;
    cout << "nr_class: " << svm_get_nr_class(model) << endl;
}

