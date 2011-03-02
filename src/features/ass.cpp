/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include <features/ass.h>
using namespace features;

#include <utils/utils.h>

#include <itpp/itbase.h>

#define RLOG_COMPONENT "ass"
#include <rlog/rlog.h>

ASS::ASS(int samplerate) : Feature(samplerate, SPECTRAL) {
    setName("ASS & ASC");
}

ASS::~ASS() {}

void 
ASS::extract(const vec& frame, vec& features) const {
    const int len = frame.length() - 1;
    
    // discard the 0-bin frequency
    vec spectrum = abs(frame.right(len));

    double summ = itpp::sum(spectrum);
  
    //vec bins("1:" + utils::stringify(len));
    vec bins = utils::linvec(1, len);
    
    if (summ == 0.0) {
        vec tmp("0 0");
        features = itpp::concat(features, tmp);
    } else {
        double centroid = itpp::sum( itpp::elem_mult(bins,spectrum) )/summ;
        double spread = itpp::sum( itpp::elem_mult( itpp::sqr(bins-centroid), spectrum ) )/summ;
        
        features = itpp::concat(features, spread);
        features = itpp::concat(features, centroid);
    }
}
