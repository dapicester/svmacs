/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H

#include "classifier.h"
using namespace model;

namespace model {

class SvmClassifier : public Classifier {

public:
    SvmClassifier();
    ~SvmClassifier();
    
    EventType classify(vec& features) const;

};

}

#endif
