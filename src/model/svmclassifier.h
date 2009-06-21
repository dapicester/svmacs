/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H

#include "classifier.h"
using namespace model;

#include <libsvm-2.0/libsvm/svm.h>
//#include <svm.h>

#include <string>
#include <stdexcept>

namespace model {

/** RuntimeException for model loading */
class BadModel : public std::runtime_error {
public:
    BadModel(const std::string& s) : std::runtime_error(s) { }
};

/** The SVM classifier */
class SvmClassifier : public Classifier {

    const struct svm_model* m1;
    const struct svm_model* model;

public:
    SvmClassifier();
    ~SvmClassifier();
    
    EventType classify(vec& features) const;

private:
    struct svm_model* getDetectionModel(bool useFile);
    struct svm_model* getClassificationModel(bool useFile);
    void debugModel(const struct svm_model* model);
};

}

#endif
