/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <features/processor.h>
#include <features/feature.h>
#include <features/zcr.h>
#include <features/energy.h>
#include <features/ass.h>
#include <features/srf.h>
#include <features/hr.h>
#include <features/mfcc.h>
using namespace features;
using itpp::vec;

#include <utils/utils.h>

#include <itpp/itsignal.h>
#include <itpp/stat/misc_stat.h>

#define RLOG_COMPONENT "processor"
#include <rlog/rlog.h>

/// Default window length in seconds (25ms)
static const double WIN_LEN = 0.025;
/// Default percentage of windows overlap (50%)
static const double WIN_OVL = 0.5;
    
/// Number of frequency bins
static const int N_FFT = 1024;
/// Number of MFCC filters
static const int N_MFCC_FILTERS = 24; 
/// Number of MFCC coefficients
static const int N_MFCC_COEFFS = 6;

/// Number of features
static const unsigned int N_FEATURES = 12;

Processor::Processor(int sr) : sampleRate(sr) {
    // define windows
    M = itpp::floor_i(WIN_LEN * sr);
    R = itpp::floor_i(WIN_OVL * M);
    win = itpp::hamming(M);
    
    // initialize feature extractors
    features[0] = new ZCR(sr);
    features[1] = new Energy(sr);  
    features[2] = new ASS(sr); 
    features[3] = new SRF(sr); 
    features[4] = new HR(sr);
    features[5] = new MFCC(sr, N_FFT - 1, N_MFCC_FILTERS, N_MFCC_COEFFS);
    
    rDebug("Processor created");
}

Processor::~Processor() {
    delete[] features;
    rDebug("Processor destroyed");
}

vec 
Processor::process(const vec& frame) {
    rDebug("process called ...");
    
    uint L = frame.length();
    //rDebug("L: %5.0f", L);
    
    uint Nframes = itpp::floor_i( (L-R) / (M-R) );
    //rDebug("Nframes: %3.0f", Nframes);
    
    vec pframe = itpp::concat(frame, utils::flipud(frame.right(R)));
    //rDebug("frame padded to length %d", pframe.length());
       
    mat mfeatures(Nframes, N_FEATURES);
    //for (uint i=0, counter=0; i<L-M-1; i+=R, counter++) {
    for (uint i = 0, counter = 0; counter < Nframes; i += R, counter++) {
        //rDebug("reading samples with index [%d,%d]", i, i+R-1);
        //rDebug("current counter  [%d]", counter);
        
        vec tmp = pframe.get(i, i + M - 1);
        //rDebug("read %d samples", tmp.length());
        
        vec current = itpp::elem_mult(tmp, win);
        vec spectrum = itpp::abs( itpp::fft( itpp::to_cvec(current), N_FFT ) ).left(N_FFT/2);
        
        //rDebug("extracting ...");
        vec feat;
        for (uint j = /*0*/0; j < /*N_EXTRACTORS*/4 ; j++) {
	    //rDebug("extracting: %s ...",features[j]->getName().c_str());
            switch (features[j]->getType()) {
            case TEMPORAL:
                features[j]->extract(current, feat); 
                break;
            case SPECTRAL: 
                features[j]->extract(spectrum, feat); 
                break;
            default:
                rError("unknown feature type: (%i)", features[j]->getType());
            }
        }
        //rDebug("feature vector: %s", vec2str(feat));
        mfeatures.set_row(counter, feat);
    }
    //rDebug("feature matrix:\n %s", mat2str(mfeatures));
    
    // data reduction
    vec vout(N_FEATURES);
    for (uint i = 0; i < N_FEATURES; i++) {
        vout.set(i, itpp::mean(mfeatures.get_col(i)) );
    }
    
    //rDebug("feature vector: %s", vec2str(vout));
    //cout << vout << endl;
    return vout;
}
