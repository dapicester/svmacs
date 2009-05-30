/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "testfeatures.h"
#include "zcr.h"
using namespace features;

#include "utils.h"

#include "gnuplot_i.hpp"

int main() {
    vec t = getTime(0, 2, 0.01);
    vec x = getSignal(t, 1.0);
    vec y = getSilence(t);

    test(x, new ZCR(100));

#ifdef PLOT
    Gnuplot* p1 = cli::plot_xy(t, x, "test");
    Gnuplot* p2 = cli::plot_xy(t, y, "silence");
    cli::pressKey();
#endif

}
