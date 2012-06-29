/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_SVMCLASSIFIER_H
#define SVMACS_SVMCLASSIFIER_H

#include "classifier.h"
#include "exceptions/exceptions.h"
#include <boost/scoped_ptr.hpp>
#include <libsvm/svm.h>

NS_SVMACS_BEGIN

/**
 * The SVM classifier.
 * A two-level classifier based on Support Vector Machines,
 * including novelty detection and classification.
 * The novelty detection step is implemented using a one-class SVM.
 * The classification is implemented using a multi-class SVM.
 * The implementation relies on the
 * \link http://www.csie.ntu.edu.tw/~cjlin/libsvm {LIBSVM} library.
 */
class SvmClassifier : public Classifier {
public:

    /**
     * Constructor.
     * @param dmodel file path to the detection model
     * @param cmodel file path to the classification model
     * @throw BadModel if cannot read the model file.
     */
    SvmClassifier(const std::string& dmodel, const std::string& cmodel);

    /// Destructor.
    ~SvmClassifier();

    /// Process audio features.
    Event::Type classify(const itpp::vec& features) const;

private:

    /**
     * Read the model from file.
     * @param path the model file path
     * @throw BadModel if cannot read the file.
     */
    svm_model* readModel(const std::string& name);

private:

    boost::scoped_ptr<svm_model> m1;    ///< The detection model.
    boost::scoped_ptr<svm_model> model; ///< The classification model.
};

NS_SVMACS_END

#endif // SVMACS_SVMCLASSIFIER_H
