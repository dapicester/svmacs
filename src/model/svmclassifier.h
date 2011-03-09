/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H

#include <model/classifier.h>

#include <libsvm/svm.h>

#include <string>
#include <stdexcept>

namespace model {

/** 
 * RuntimeException for model loading 
 */
class BadModel : public std::runtime_error {
public:
    BadModel(const std::string& s) : std::runtime_error(s) {}
};

/** 
 * The SVM classifier 
 */
class SvmClassifier : public Classifier {
public:
    SvmClassifier();
    ~SvmClassifier();
    
    EventType classify(itpp::vec& features) const;

private:
    const struct svm_model* m1;
    const struct svm_model* model;
    
    /// read the model from file
    struct svm_model* readModel(const std::string& name);
};

}

#endif
