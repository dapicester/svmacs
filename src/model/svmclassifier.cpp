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
    rDebug("constructor invoked");
    
    rDebug("loading Detection model ...");
    m1 = getDetectionModel(true);
    
    rDebug("loading Classification model ...");
    model = getClassificationModel(true);
    
    rDebug("SvmClassifier created");
}

svm_model* SvmClassifier::getDetectionModel(bool useFile) {
    const char* MODEL = "m1";
    struct svm_model* m1;
    
    if (useFile) {
        rInfo("reading model file: %s", MODEL);
        m1 = svm_load_model(MODEL);
        if (m1 == NULL) {
            std::string message = "Detection model is NULL!";
            rError("%s", message.c_str());
            throw BadModel(message);
        }
    } else {
        rInfo("creating model from scratch");
        //TODO
        m1 = NULL;
        rError("model is NULL");
    }
    return m1;
}

svm_model* SvmClassifier::getClassificationModel(bool useFile) {
    const char* MODEL  = "model";
    struct svm_model* model;
    
    if (useFile) {
        rInfo("reading model file: %s", MODEL);
        model = svm_load_model(MODEL);
        if (model == NULL) {
            std::string message = "Classification model is NULL!";
            rError("%s", message.c_str());
            throw BadModel(message);
        }
    } else {
        rInfo("creating model from scratch");
        //TODO
        model = NULL;
        rError("model is NULL");
    }
    return model;
}

SvmClassifier::~SvmClassifier(){
    rDebug("SvmClassifier destructed");
}

EventType SvmClassifier::classify(vec& features) const { 
#if 1
#ifdef ENABLE_LOG
    rDebug("feature vector:");
    std::cout << features << std::endl;
#endif
#endif

    //rDebug("scaling data");
    features = scaleData(features, getRange());

#if 0
#ifdef ENABLE_LOG
    rDebug("scaled vector:");
    std::cout << features << std::endl;
#endif
#endif

    // build the array
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
#ifdef ENABLE_LOG 
    // debug array
    for (int i=0; i<len+1; i++) {
       rDebug("array[%d]:  index=%d  value=%f", i, array[i].index, array[i].value);
    }
#endif
#endif

    EventType t = NONE;
    
#if 0 // enable detection step
    //rDebug("detection");
    int detected = svm_predict(m1, array);
    rDebug("detection = %d", detected);
#else // classification without detection
    int detected(1);
#endif

#if 1 // enable classification step
    //detected = 1;
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

