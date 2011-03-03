/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include <iostream>
using namespace std;

#include <libsvm/svm.h>

void test_model(const svm_model* model) {
    cout << (model == NULL ? "null" : "not null") << endl;
    
    cout << "svm_type: " << svm_get_svm_type(model) << endl;
    cout << "nr_class: " << svm_get_nr_class(model) << endl;
    
}

int main() {
    cout << "m1" << endl;
    const char* m1_file = "/home/paolo/projects/svmacs/bin/m1";
    const svm_model* m1 = svm_load_model(m1_file);
    test_model(m1);
    
    cout << "model" << endl;
    const char* model_file = "/home/paolo/projects/svmacs/bin/model";
    const svm_model* model = svm_load_model(model_file);
    test_model(model);
}
