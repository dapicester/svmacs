/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "energy.h"
using namespace features;

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

Energy::Energy(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

Energy::~Energy() {}

float* Energy::extract(const float* frame) const {

    return 0;
}
