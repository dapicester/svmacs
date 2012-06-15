/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "zcr.h"

#include <itpp/itbase.h>
using itpp::vec;

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

ZCR::ZCR(int samplerate) : Feature(samplerate, TEMPORAL) {
    name = "ZCR";
}

ZCR::~ZCR() {}

const int INDEX = 0;

void
ZCR::extract(const vec& frame, vec* features) const {
    const int len = frame.length();

    // get the sign
    vec sign = itpp::sign(frame);
    vec shft = itpp::concat(sign[0], sign.left(len - 1));

    // differentiate
    int cont = 0;
    int diff;
    for (int  i = 0; i < len; i++) {
        diff = sign[i] - shft[i];
        // count non-zero elements
        if (diff != 0) {
            cont++;
        }
    }

    double zcr = static_cast<double>(cont) / len * samplerate;
    (*features)[INDEX] = zcr;
}

NS_SVMACS_END
