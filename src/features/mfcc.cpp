/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "mfcc.h"
using namespace features;

#include "convert.h"
using utils::stringify;

#define RLOG_COMPONENT "mfcc"
#include <rlog/rlog.h>

#define PRINT(X) cout << #X << ": " << X << endl;
#define PR(X) cout << X << endl;

MFCC::MFCC(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

MFCC::~MFCC() {}

inline Type MFCC::getType() const { return SPECTRAL; }

void MFCC::setFilterBank(const mat* fb) {
    filterBank = fb;
}

const mat* MFCC::getMelFilters(const int& Nfft, const int& Fs, const int& Nfilters) {
    const double freqMin = 0, freqMax = Fs/2;
    mat* wts = new mat(Nfilters, Nfft);
    
    vec tmp = "0 : " + stringify(Nfilters+1);

    // extract frequency of each fft bin
    vec fft_freqs = "0 : " + stringify(Nfft-1);
    fft_freqs *= static_cast<double>(Fs)/Nfft; //PRINT(fft_freqs);
    
    double melMin = 2595 * log10(1+freqMin/700); //PRINT(melMin);
    double melMax = 2595 * log10(1+freqMax/700); //PRINT(melMax);
    
    vec bin_freqs = 700 * ( pow10( (melMin + tmp / (Nfilters+1) * (melMax-melMin)) / 2595 ) - 1 );
    //PRINT(bin_freqs);

    vec bins = round(bin_freqs/Fs*(Nfft-1));
    //PRINT(bins);

    for (int i=0; i<Nfilters; i++) {
	ivec idx = "0 1 2";
        vec freqs = bin_freqs(idx+i);
	//PRINT(freqs);

        // lower and upper slopes for all bins
        vec loslope = (fft_freqs - freqs[0])/(freqs[1] - freqs[0]); //PRINT(loslope);
        vec hislope = (freqs[2] - fft_freqs)/(freqs[2] - freqs[1]); //PRINT(hislope);

        //.. then intersect them with each other and zero
	mat m1(2,Nfft);
	m1.set_row(0,loslope);
	m1.set_row(1,hislope); 
	
	mat m2(2,Nfft);
	m2.zeros();
	m2.set_row(1, min(m1));
        
        wts->set_row(i, max(m2)); //PRINT(wts->get_row(i));
    }

    // Make sure 2nd half of FFT is zero
    //wts(:,(Nfft/2+1):Nfft) = 0;
    //mat zeros(wts->rows(),Nfft/2);
    //zeros.zeros();
    //wts->set_cols(Nfft/2+1, zeros);
    //PRINT(*wts);
    return wts;
}

void MFCC::extract(const vec& frame, vec& features) const {
    mat spectrum(frame);
    mat energy = (*filterBank) * spectrum.hermitian_transpose();
    PR("oooo");
}
