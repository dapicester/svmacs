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

ZCR::~ZCR() {}

float* ZCR::extract(const float* frame) const {

    return 0;
}
