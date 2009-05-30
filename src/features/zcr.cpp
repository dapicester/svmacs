/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "zcr.h"
using namespace features;

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

ZCR::ZCR(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

ZCR::~ZCR() { type = TEMPORAL; }

vec ZCR::extract(const vec& frame) const {
    const int len = frame.length();

    vec sgn = sign(frame); 
    //PRINT(sgn);
    
    double cont = 0;
    for (int  i = 0; i < len - 2; i++) {
        if ( (sgn[i+1] - sgn[i]) != 0 )
             cont++;
    }
    //PRINT(cont);

    double zcr = cont / len * getSamplerate();
    //PRINT(zcr);
    
    vec ret(&zcr, 1); 
    //PRINT(ret);
    return ret;
}
