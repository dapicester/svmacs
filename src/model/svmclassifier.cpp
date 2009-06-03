/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "svmclassifier.h"
using namespace model;

#include "range.h"

#include <itpp/itbase.h>
using namespace itpp;

#define RLOG_COMPONENT "svmclassifier"
#include <rlog/rlog.h>

SvmClassifier::SvmClassifier() : Classifier() {
    m1 = svm_load_model("m1");
    model = svm_load_model("model");
    rDebug("SvmClassifier created");
}

SvmClassifier::~SvmClassifier(){
    rDebug("SvmClassifier destructed");
}

EventType SvmClassifier::classify(vec& features) const {
    features = scaleData(features, getRange());
    
    const int len = features.length();
    svm_node array[len];

    for(int i=0; i< len; i++) {
         array[i].index = i;
         array[i].value = features[i];
    }

    // detect
    int detected = svm_predict(m1, array);
    EventType t = NONE;
    const char* description = "None";
    if (detected == 1) {
        int type = svm_predict(model, array);

        switch (type) {
        case GUNSHOT:
           t = GUNSHOT;
           description = "Gunshot";
           break;
        case SCREAM:
           t = SCREAM;
           description = "Scream";
           break;
        case GLASS:
           t = GLASS;
           description = "Glass";
           break;
        }
        rInfo("Event Detected: %s!", description);
    }
    return t;
}
