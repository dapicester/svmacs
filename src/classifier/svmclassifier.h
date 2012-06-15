/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H

#include "classifier.h"
#include "exceptions/exceptions.h"
#include <libsvm/svm.h>

NS_SVMACS_BEGIN

/** 
 * The SVM classifier 
 */
class SvmClassifier : public Classifier {
public:
    SvmClassifier();
    ~SvmClassifier();
    
    EventType classify(itpp::vec& features) const;

private: // TODO: boost::scoped_ptr
    
    const struct svm_model* m1;
    const struct svm_model* model;
    
    /// read the model from file
    struct svm_model* readModel(const std::string& name) throw (BadModel);
};

NS_SVMACS_END

#endif
