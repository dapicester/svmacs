/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "mfcc.h"

#include <itpp/itbase.h>
using itpp::vec;
using itpp::mat;

#define RLOG_COMPONENT "mfcc"
#include <rlog/rlog.h>

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

static const int MEL_COEFF = 2595;
static const int MEL_DEN = 700;

#define LOAD_FILE

void MFCC::initFilterBank() {
#ifdef LOAD_FILE
    std::string file_path = "/home/paolo/NetBeansProjects/svmacs/"
                            "src/model/melfb.it";
    rInfo("loading Mel FilterBank from file %s ...", file_path.c_str());

    itpp::it_file file;
    file.open(file_path);
    file >> itpp::Name("wts") >> filterBank;
    file.close();
    rInfo("done");
#else
    const double freqMin = double(0);
    const double freqMax = double(samplerate/2);

    mat wts = itpp::zeros(nfilters, nfft);

    /* extract frequency of each fft bin */
    vec fft_freqs = "0 : " + lexical_cast<std::string > (nfft - 1);
    fft_freqs /= nfft;
    fft_freqs *= samplerate;
    //rDebug("fft_freqs:\n%s", itpp::to_str(fft_freqs).c_str());

    const double melMin = MEL_COEFF * std::log10(1 + freqMin/MEL_DEN);
    const double melMax = MEL_COEFF * std::log10(1 + freqMax/MEL_DEN);
    //rDebug("melMin = %2.9f\tmelMax = %2.9f", melMin, melMax);

    vec tmp = "0 : " + lexical_cast<std::string > (nfilters + 1);
    tmp /= (nfilters + 1);
    tmp *= (melMax - melMin);
    //rDebug("tmp:\n%s", itpp::to_str(tmp).c_str());

    const vec bin_freqs = MEL_DEN * ( itpp::pow10((melMin + tmp) / MEL_COEFF) - 1 );
    //rDebug("bin_freqs:\n%s", itpp::to_str(bin_freqs).c_str());

    for (int i = 0; i < nfilters; i++) {
        const vec freqs = bin_freqs(itpp::ivec("0 1 2") + i);
        //rDebug("filtro %d\n%s", i+1, itpp::to_str(freqs).c_str());

        /* get lower and upper slopes for all bins ... */
        const vec loslope = (fft_freqs - freqs[0]) / (freqs[1] - freqs[0]);
        const vec hislope = (freqs[2] - fft_freqs) / (freqs[2] - freqs[1]);
        //rDebug("loslope:\n%s", itpp::to_str(loslope).c_str());
        //rDebug("hislope:\n%s", itpp::to_str(hislope).c_str());

        /* ... then intersect them with each other and zero */
        mat m1 = itpp::zeros(2, nfft);
        m1.set_row(0, loslope);
        m1.set_row(1, hislope);

        mat m2 = itpp::zeros(2, nfft);
        m2.set_row(1, itpp::min(m1));

        const vec row = itpp::max(m2);
        //rDebug("row:\n%s", itpp::to_str(row).c_str());

        wts.set_row(i, row);
    }
    /* use only the 1st half of FFT */
    filterBank = wts.get_cols(0, nfft/2 - 1);
#endif
}
