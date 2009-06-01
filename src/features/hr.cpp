/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "hr.h"
using namespace features;

#include "utils.h"
using namespace utils;

#include <itpp/signal/sigfun.h>
using namespace itpp;

#define RLOG_COMPONENT "hr"
#include <rlog/rlog.h>

HR::HR(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

HR::~HR() {}

inline Type HR::getType() const { return TEMPORAL; }

void HR::extract(const vec& frame, vec& features) const {
    double out = 0.0;
    
    if (numel(find(frame)) != 0) { // no silence
        vec R = xcorr(frame, -1, "coeff");
        const int rlen = R.length();
        
        R = R.right(rlen-rlen/2);
        
        ivec idx = maxima(R);
        vec maxval = R(idx);
        
        const int mlen = maxval.length();
        if ( mlen != 1) { // more than one peek
            out = max(maxval.right(mlen - 1));
        }
    }
    
    features = concat(features, out);
}
