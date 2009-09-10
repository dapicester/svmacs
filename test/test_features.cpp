/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#define INPUT_FILE_NAME "test_signal.it"
#define OUTPUT_FILE_NAME "features.it"

#define TEST_SIGNAL "test_signal"

#define TEST_DOUBLE "double.it"

using namespace std;

#include <itpp/itsignal.h>
using namespace itpp;

#include "feature.h"
#include "zcr.h"
#include "energy.h"
#include "ass.h"
#include "srf.h"
#include "hr.h"
#include "mfcc.h"
using namespace features;

int main() {
  const int sr = 22050, Nfft = 1024, N = 6;

  // load signal
  it_ifile ff;
  ff.open(INPUT_FILE_NAME);

  vec test_signal;
  ff >> Name(TEST_SIGNAL) >> test_signal;
  //std::cout << test_signal << std::endl;

  // compute spectrum
  vec spectrum = abs(fft(to_cvec(test_signal), Nfft)).left(Nfft/2);

  // init features
  Feature* features[6];
  features[0] = new ZCR(sr);
  features[1] = new Energy(sr);  
  features[2] = new ASS(sr); 
  features[3] = new SRF(sr); 
  features[4] = new HR(sr);
  MFCC* mfcc = new MFCC(sr);
  const mat* fb = MFCC::getMelFilters(Nfft-1, sr, 24); //N_MFCC_FILTERS
  mfcc->setFilterBank(fb);
  features[5] = mfcc;

  // extract features
  vec feat;
  for (int i = 0; i<N; i++) {
    cout << features[i]->getName() << " ";
    switch (features[i]->getType()) {
      case TEMPORAL:
           features[i]->extract(test_signal, feat); 
           break;
      case SPECTRAL: 
           features[i]->extract(spectrum, feat); 
           break;
    }
  }
  cout << endl << "features: " << feat << endl;

  // saving to file
  it_file of(OUTPUT_FILE_NAME);
  of << Name("feat") << feat;
  cout << "saved to file " << OUTPUT_FILE_NAME << endl;
  
  return 0;
}
