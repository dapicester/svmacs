/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <model/range.h>
#include <model/svmclassifier.h>
using namespace model;

#include <itpp/itbase.h>
using namespace itpp;

#define RLOG_COMPONENT "svmclassifier"
#include <rlog/rlog.h>

static const std::string M1 = "m1";
static const std::string MC = "model";

SvmClassifier::SvmClassifier() : Classifier() {
    rDebug("constructor invoked");
    
    rDebug("loading Detection model %s ...", M1.c_str());
    m1 = readModel(M1);
    
    rDebug("loading Classification model %s ...", MC.c_str());
    model = readModel(MC);
    
    rDebug("SvmClassifier created");
}

SvmClassifier::~SvmClassifier(){
    rDebug("destructor invoked");
    
    delete m1;
    delete model;
    
    rDebug("SvmClassifier destroyed");
}

svm_model*
SvmClassifier::readModel(const std::string& name) {
    rInfo("reading model file: %s", name.c_str());
    struct svm_model* model = svm_load_model(name.c_str());
    if (model == NULL) {
        std::string message = "Model " + name + " is NULL!";
        rError("%s", message.c_str());
        throw BadModel(message);
    }
    return model;
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

