/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include <features/mfcc.h>
using namespace features;

#include <utils/convert.h>

#define RLOG_COMPONENT "mfcc"
#include <rlog/rlog.h>

MFCC::MFCC(int samplerate, int n, int nf) : Feature(samplerate, SPECTRAL), nfft(n), nfilters(nf) {
  setName("MFCC");
  initFilterBank();
}

MFCC::~MFCC() {}

const mat* 
MFCC::initFilterBank() {
  const double freqMin = 0;
  const double freqMax = samplerate/2;
  mat wts(nfilters, nfft);
 
  vec tmp = "0 : " + utils::stringify(nfilters + 1);

  // extract frequency of each fft bin
  vec fft_freqs = "0 : " + utils::stringify(nfft - 1);
  fft_freqs *= static_cast<double>(samplerate)/nfft;
   
  double melMin = 2595 * itpp::logb(10, 1 + freqMin/700 );
  double melMax = 2595 * itpp::logb(10, 1 + freqMax/700 );
  
  vec bin_freqs = 700 * ( itpp::pow10( (melMin + tmp / (nfilters + 1) * (melMax - melMin)) / 2595 ) - 1 );
  vec bins = itpp::round( bin_freqs / samplerate * (nfft-1) );

  for (int i = 0; i < nfilters; i++) {
    itpp::ivec idx = "0 1 2";
    vec freqs = bin_freqs(idx + i);

    // lower and upper slopes for all bins
    vec loslope = (fft_freqs - freqs[0])/(freqs[1] - freqs[0]);
    vec hislope = (freqs[2] - fft_freqs)/(freqs[2] - freqs[1]);

    // ... then intersect them with each other and zero
    mat m1(2, nfft);
    m1.set_row(0, loslope);
    m1.set_row(1, hislope); 

    mat m2(2, nfft);
    m2.zeros();
    m2.set_row(1, itpp::min(m1));
        
    wts.set_row(i, itpp::max(m2));
  }

  // Make sure 2nd half of FFT is zero
  return new mat( wts.get_cols(0, nfft/2) );
}

void 
MFCC::extract(const vec& frame, vec& features) const {
    mat spectrum(frame);   
    mat energy = ((*filterBank) * spectrum) + 1;
    
    int numFilters = filterBank->rows();
    
    mat a = "0 : " + utils::stringify(N_MFCC);
    mat b = "1 : " + utils::stringify(numFilters);
    mat c = (a.hermitian_transpose() * (b - 0.5));
    mat d = itpp::log10(energy);
    mat coeffs = itpp::cos(c * (itpp::pi/numFilters)) * d;
    
    features = itpp::concat(features, coeffs.get_col(0).right(N_MFCC));
}
