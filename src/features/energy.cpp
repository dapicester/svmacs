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

vec Energy::extract(const vec& frame) const {
    //rDebug("Energy->extract()");
    vec ret(1);
    return ret;
}
