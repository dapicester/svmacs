/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <features/zcr.h>
using namespace features;

#include <itpp/base/math/elem_math.h>

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

ZCR::ZCR(int samplerate) : Feature(samplerate, TEMPORAL) {
    setName("ZCR");
}

ZCR::~ZCR() {}

void 
ZCR::extract(const vec& frame, vec& features) const {
    const int len = frame.length();

    vec sgn = itpp::sign(frame); 
    
    double cont = 0;
    for (int  i = 0; i < len - 2; i++) {
        if ( (sgn[i+1] - sgn[i]) != 0 )
             cont++;
    }

    double zcr = cont / len * samplerate;
    
    features = itpp::concat(features, zcr); 
}
