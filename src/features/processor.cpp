/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "processor.h"
#include "feature.h"
#include "zcr.h"
#include "energy.h"
using namespace features;

#define RLOG_COMPONENT "processor"
#include <rlog/rlog.h>

Processor::Processor(int sr) : sampleRate(sr) {
    
    features[0] = new ZCR(sr);
    features[1] = new Energy(sr);    
     
    rDebug("Processor created");
}

Processor::~Processor() {
    rDebug("Processor destructed");
}

float* Processor::process(const float* frame) {
    rDebug("calling process ...");
    for (int i=0; i<fsize; i++) {
        rDebug("extracting: %s ...",features[i]->getName().c_str());
        features[i]->extract(frame);
    }
    
    return 0;
}
