/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "processor.h"
#include "feature.h"
#include "zcr.h"
#include "energy.h"
#include "ass.h"
using namespace features;

#include "utils.h"
using namespace utils;

#define RLOG_COMPONENT "processor"
#include <rlog/rlog.h>

Processor::Processor(int sr) : sampleRate(sr) {
    // define windows
    M = floor(WIN_LEN * sr);
    R = floor(WIN_OVL * M);
    win = hamming(M);
    
    features[0] = new ZCR(sr);
    features[1] = new Energy(sr);  
    features[2] = new ASS(sr);  
     
    rDebug("Processor created");
}

Processor::~Processor() {
    rDebug("Processor destructed");
}

vec Processor::process(const vec& frame) {
    rDebug("process called ...");
    
    // frame padding
    vec pframe(frame);
    pframe.ins(frame.length(), flipud(frame.right(R)));
    // TODO init altre features
    
    // process frame
    vec out(N_FEATURES);
    for (int i=0; i<pframe.length(); i+=R) {
        vec curr = elem_mult( pframe.get(i, i+R-1), win);
        cvec spectrum = fft(to_cvec(curr),N_FFT);
      
        //out.ins(0, features[0]->extract(curr)); // ZCR
        //out.ins(1, features[1]->extract(curr)); // energy
        //out.ins(2, features[2]->extract(curr)); // ASC, ASS
              
        for (uint j=0; j<N_FEAT; j++) {
            //rDebug("extracting: %s ...",features[i]->getName().c_str());
            //FIXME aggiustare
            //vec feat = features[j]->extract(curr);
            //out.ins(out.length(), feat);
        }
        
    }
    
    // TODO data reduction
    return out;
}
