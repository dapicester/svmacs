/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <features/hr.h>
using namespace features;
using itpp::vec;

#include <utils/utils.h>

#include <itpp/itsignal.h>

#define RLOG_COMPONENT "hr"
#include <rlog/rlog.h>

HR::HR(int samplerate) : Feature(samplerate, TEMPORAL) {
  setName("HR");
}

HR::~HR() {}

void
HR::extract(const vec& frame, vec& features) const {
  double out = 0.0;
  
  if (utils::numel(utils::find(frame)) != 0) { // no silence
    vec R = itpp::xcorr(frame, -1, "coeff");
    const int rlen = R.length();
    
    R = R.right(rlen-rlen/2);
    
    ivec idx = utils::maxima(R);
    vec maxval = R(idx);
    
    const int mlen = maxval.length();
    if ( mlen != 1) { // more than one peek
      out = itpp::max(maxval.right(mlen - 1));
    }
  }
  
  features = itpp::concat(features, out);
}
