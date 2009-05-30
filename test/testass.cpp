/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "testfeatures.h"
#include "ass.h"
using namespace features;

#include "utils.h"

#include "gnuplot_i.hpp"

int main() {
    vec t = getTime(0, 2, 0.01);
    vec x = getSignal(t, 1.0);
    vec y = getSilence(t);

    vec sx = abs(fft(to_cvec(x), N_FFT)).left(N_FFT/2);
    vec sy = abs(fft(to_cvec(y), N_FFT)).left(N_FFT/2);

    test(sx, new ASS(100));
    test(sy, new ASS(100));

#ifdef PLOT
    Gnuplot* p1 = cli::plot_xy(t, x, "test");
    Gnuplot* p2 = cli::plot_x(sx, "abs(spectrum(test))");
    Gnuplot* p3 = cli::plot_xy(t, y, "silence");
    Gnuplot* p4 = cli::plot_x(sy, "abs(spectrum(silence))");
    cli::pressKey();
#endif

}
