/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "ass.h"
#include "utils/utils.h"

#include <itpp/itbase.h>
using itpp::vec;

#define RLOG_COMPONENT "ass"
#include <rlog/rlog.h>

ASS::ASS(int samplerate) : Feature(samplerate, SPECTRAL) {
    name = "ASS and ASC";
}

ASS::~ASS() {}

static const int INDEX = 2;

void ASS::extract(const vec& spectrum, vec& features) const {
    const int len = spectrum.length() - 1;
    
    // discard the 0-bin frequency
    vec aspectrum = abs(spectrum.right(len));

    double summ = itpp::sum(aspectrum);
    vec bins = linvec(1, len);
    
    double centroid = 0.0;
    double spread = 0.0;
    if (summ > 0.0) {
        centroid = itpp::sum( 
                              itpp::elem_mult(bins, aspectrum) 
                          ) / summ;
        spread = itpp::sum( 
                            itpp::elem_mult( itpp::sqr(bins - centroid), aspectrum) 
                        )/summ;
    }
    
    features[INDEX] = centroid;
    features[INDEX + 1] = spread;
}
