/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "testfeatures.h"
#include "energy.h"
using namespace features;

#ifdef PLOT
#include "utils.h"
#include "plot.h"
#include "gnuplot_i.hpp"
#endif

int main() {
    vec t = getTime(0, 2, 0.01);
    vec x = getSignal(t, 1.0);
    vec y = getSilence(t);

    vec feat;
    test(x, new Energy(100), feat);

#ifdef PLOT
    Gnuplot* p1 = cli::plot_xy(t, x, "test");
    Gnuplot* p2 = cli::plot_xy(t, y, "silence");
    cli::pressKey();
#endif

}
