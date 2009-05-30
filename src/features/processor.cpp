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
using utils::flipud;

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
    
    vec pframe(frame);
    pframe.ins(frame.length(), flipud(frame.right(R)));
    //rDebug("frame padded to length %d", pframe.length());
   
    // TODO init altre features
    
    //rDebug("process frame");
    vec out;
    for (int i=0; i<pframe.length()-R; i+=R) {
        //rDebug("reading samples with index [%d,%d]", i, i+R-1);
        vec current = elem_mult( pframe.get(i, i+R-1), win);
        vec spectrum = abs(fft(to_cvec(current), N_FFT)).left(N_FFT/2);
        
        //rDebug("extracting");
        for (uint j=0; j<N_FEAT-1; j++) {
            //rDebug("extracting: %s ...",features[i]->getName().c_str());
            vec feat;
            switch (features[j]->getType()) {
            case TEMPORAL: features[j]->extract(current); break;
            case SPECTRAL: features[j]->extract(spectrum); break;
            }
            //concat(out, feat);
        }
    }
    
    // TODO data reduction
    return out;
}
