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
    rDebug("SvmClassifier created");
}

SvmClassifier::~SvmClassifier(){
    rDebug("SvmClassifier destructed");
}

EventType SvmClassifier::classify(vec& features) const {
    features = scaleData(features, getRange());
    //TODO 
    
    return NONE;
}
