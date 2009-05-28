/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "ass.h"
using namespace features;

#define RLOG_COMPONENT "ass"
#include <rlog/rlog.h>

ASS::ASS(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

ASS::~ASS() {}

vec ASS::extract(const vec& frame) const {
    const int len = frame.length() - 1;
    
    // discard the 0-bin frequency
    vec spectrum = abs(frame.right(len));

    double summ = sum(spectrum);
    //PRINT(summ);

    vec bins(len);
    for (int i=0; i<len; i++) {
        bins[i] = i+2;
    }
    //PRINT(bins);
    
    double tmp[2];
    if (summ == 0.0) {
        tmp[0] = 0.0;
        tmp[1] = 0.0;
    } else {
        double centroid = sum(elem_mult(spectrum, bins))/summ;
        PRINT(centroid);
        double spread = sum(elem_mult(sqr(spectrum - centroid), bins))/summ;
        PRINT(spread);

        tmp[0] = spread;
        tmp[1] = centroid;
    }
    
    vec out(tmp,2);
    return out;
}
