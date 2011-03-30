/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "zcr.h"

#include <itpp/itbase.h>
using itpp::vec;

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

ZCR::ZCR(int samplerate) : Feature(samplerate, TEMPORAL) {
    name = "ZCR";
}

ZCR::~ZCR() {}

static const int INDEX = 0;

void 
ZCR::extract(const vec& frame, vec& features) const {
    const int len = frame.length();

    // get the sign
    vec sign = itpp::sign(frame); 
    
    // differentiate
    int cont = 0;
    for (int  i = 0; i < len - 2; i++) {
        int diff = sign[i] - sign[i + 1];
        // count non-zero elements
        if (diff != 0)
             cont++;
    }

    double zcr = static_cast<double>(cont) / len * samplerate;
    features[INDEX] = zcr; 
}
