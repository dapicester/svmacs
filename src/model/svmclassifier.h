/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H

#include "classifier.h"
using namespace model;

#include <libsvm-2.0/libsvm/svm.h>

namespace model {

class SvmClassifier : public Classifier {
    //static const string M1 = "m1.model";
    //static const string MODEL = "model.model";

    const struct svm_model* m1;
    const struct svm_model* model;

public:
    SvmClassifier();
    ~SvmClassifier();
    
    EventType classify(vec& features) const;

};

}

#endif
