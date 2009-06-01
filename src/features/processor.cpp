/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "processor.h"
#include "feature.h"
#include "zcr.h"
#include "energy.h"
#include "ass.h"
#include "srf.h"
#include "hr.h"
using namespace features;

#include "utils.h"
using utils::flipud;

#include <itpp/itsignal.h>
using namespace itpp;
#include <itpp/stat/misc_stat.h>
using itpp::mean;

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
    features[3] = new SRF(sr); 
    features[4] = new HR(sr);
/*    MFCC* mfcc = new MFCC(sr);
    mat* fb = generateFilter(N_FFT, sr, N_MFCC_FILTERS);
    mfcc->setFilterBanK(fb);
    features[5] = mfcc;*/
     
    rDebug("Processor created");
}

Processor::~Processor() {
    rDebug("Processor destructed");
}

vec* Processor::process(const vec& frame) {
    rDebug("process called ...");
    
    double L = frame.length();
    //rDebug("L: %f", L);
    
    double Nframes = floor((L-R)/(M-R));
    //rDebug("Nframes: %f", Nframes);
    
    vec pframe = concat(frame, flipud(frame.right(R)));
    //rDebug("frame padded to length %d", pframe.length());
   
    // TODO init altre features
    
    //rDebug("process frame");    
    mat mfeatures(Nframes, N_FEATURES);
    for (uint i=0, counter=0; i<L-M-1; i+=R, counter++) {
        //rDebug("reading samples with index [%d,%d]", i, i+R-1);
        
        vec current = elem_mult( pframe.get(i, i+R-1), win);
        vec spectrum = abs(fft(to_cvec(current), N_FFT)).left(N_FFT/2);
        
        //rDebug("extracting");
        vec feat;
        for (uint j=0; j<N_FEAT; j++) {
            //rDebug("extracting: %s ...",features[j]->getName().c_str());
            switch (features[j]->getType()) {
            case TEMPORAL:
                features[j]->extract(current, feat); 
                break;
            case SPECTRAL: 
                features[j]->extract(spectrum, feat); 
                break;
            }
        }
        //cout << "feat: " << feat << endl;
        mfeatures.set_row(counter, feat);
    }
    //cout << "mfeatures: " << mfeatures << endl;
    
    // data reduction
    vec* out = new vec(N_FEATURES);
    for (uint i=0; i<N_FEATURES; i++) {
        out->set(i, mean( mfeatures.get_col(i)));
    }
    //cout << "out: " << *out << endl;
    return out;
}
