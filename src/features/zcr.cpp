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

vec ZCR::extract(const vec& frame) const {

    return 0;
}
