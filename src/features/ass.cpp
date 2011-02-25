/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "ass.h"
using namespace features;

#include "utils/utils.h"

#include <itpp/itbase.h>

#define RLOG_COMPONENT "ass"
#include <rlog/rlog.h>

ASS::ASS(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

ASS::~ASS() {}

inline Type ASS::getType() const { return SPECTRAL; }

void ASS::extract(const vec& frame, vec& features) const {
    const int len = frame.length() - 1;
    
    // discard the 0-bin frequency
    vec spectrum = abs(frame.right(len));

    double summ = sum(spectrum);
  
    //vec bins("1:" + utils::stringify(len));
    vec bins = utils::linvec(1, len);
    
    if (summ == 0.0) {
        vec tmp("0 0");
        features = concat(features, tmp);
    } else {
        double centroid = sum(elem_mult(bins,spectrum))/summ;
        double spread = sum(elem_mult(sqr(bins-centroid), spectrum))/summ;
        
        features = concat(features, spread);
        features = concat(features, centroid);
    }
}
