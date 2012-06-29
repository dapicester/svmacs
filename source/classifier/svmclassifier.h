/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H

#include "classifier.h"
#include "exceptions/exceptions.h"
#include <boost/scoped_ptr.hpp>
#include <libsvm/svm.h>

NS_SVMACS_BEGIN

/**
 * The SVM classifier
 */
class SvmClassifier : public Classifier {
public:

    /**
     * Constructor.
     * @param dmodel file path to the detection model
     * @param cmodel file path to the classification model
     */
    SvmClassifier(const std::string& dmodel, const std::string& cmodel);

    /// Destructor.
    ~SvmClassifier();

    /// Process audio features.
    Event::Type classify(itpp::vec& features) const;

private: // TODO: boost::scoped_ptr

    boost::scoped_ptr<svm_model> m1;
    boost::scoped_ptr<svm_model> model;

    /// Read the model from file
    svm_model* readModel(const std::string& name) throw (BadModel);
};

NS_SVMACS_END

#endif
