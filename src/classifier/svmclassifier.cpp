/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "svmclassifier.h"
#include "model/range.h"

#include <itpp/itbase.h>
#include <libsvm/svm.h>

#define RLOG_COMPONENT "svmclassifier"
#include <rlog/rlog.h>

static const std::string M1 = "m1";
static const std::string MC = "model";

SvmClassifier::SvmClassifier() : Classifier() {
    rDebug("loading Detection model ...");
    m1 = readModel(M1);
    
    rDebug("loading Classification model ...");
    model = readModel(MC);
    
    rInfo("SvmClassifier created");
}

SvmClassifier::~SvmClassifier(){
    delete m1;
    delete model;
    rInfo("SvmClassifier correctly destroyed");
}

svm_model* SvmClassifier::readModel(const std::string& name) throw (BadModel) {
    struct svm_model* model = svm_load_model(name.c_str());
    if (model == NULL) {
        std::string message = "Model " + name + " is NULL!";
        rError("%s", message.c_str());
        throw BadModel(message);
    }
    rDebug("loaded model file: %s", name.c_str());
    return model;
}

EventType SvmClassifier::classify(itpp::vec& features) const { 
    //rDebug("feature vector: %s", itpp::to_str(features).c_str());

    //rDebug("scaling data");
    features = scaleData(features, getRange());

    //rDebug("scaled vector: %s", itpp::to_str(features).c_str());

    // build the array for libsvm
    const int len = features.length();
    svm_node array[len+1];

    int i = 0;
    while(i<len) {
         array[i].index = i+1;
         array[i].value = features[i];
         i++;
    }
    // mark the last element
    array[i].index = -1;
    array[i].value = 0.0;

#if 0
    for (int i=0; i<len+1; i++) {
       rDebug("array[%d]:  index=%d  value=%f", i, array[i].index, array[i].value);
    }
#endif
    
#if 1 // enable/disable detection step
    int detected = svm_predict(m1, array);
    rDebug("detection = %d", detected);
#else // classification without detection
    int detected = 1;
#endif

    EventType t = NONE;
#if 1 // enable/disable classification step
    if (detected == 1) { 
        int type = svm_predict(model, array);
        rDebug("classification = %d", type);
        switch (type) {
        case GUNSHOT: t = GUNSHOT; break;
        case SCREAM:  t = SCREAM;  break;
        case GLASS:   t = GLASS;   break;
        } 
    }
#endif
    
    return t;
}
