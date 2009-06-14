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
    m1 = svm_load_model("m1");
    if (m1 == NULL)
        rError("Detection model is NULL!");
    
    rDebug("loading Classification model ...");
    model = svm_load_model("model");
    if (model == NULL)
        rError("Classification model is NULL!");
    
    rDebug("SvmClassifier created");
}

SvmClassifier::~SvmClassifier(){
    rDebug("SvmClassifier destructed");
}

EventType SvmClassifier::classify(vec& features) const { 
    //rDebug("scaling data");
    features = scaleData(features, getRange());
    
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

#ifdef ENABLE_DEBUG
    for (int i=0; i<len+1; i++) {
       rDebug("array[%d]:  index=%d  value=%f",i,array[i].index,array[i].value);
    }
#endif
    
    rDebug("detection");
    int detected = svm_predict(m1, array);
    rDebug("detected: %d", detected);

    EventType t = NONE;
    if (detected == 1) {
        rDebug("classification");
        int type = svm_predict(model, array);
        switch (type) {
        case GUNSHOT: t = GUNSHOT; break;
        case SCREAM:  t = SCREAM;  break;
        case GLASS:   t = GLASS;   break;
        } 
    }
    return t;
/*    
    int detected = svm_predict(m1, array);
    EventType t = NONE;
    const char* description = "None";
    
    if (detected == 1) {
        rDebug("classification");
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
    } else {
        rDebug("nothing detected");
    }
    return t;
 */
}
