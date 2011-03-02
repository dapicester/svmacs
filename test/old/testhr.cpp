/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "testfeatures.h"
#include <features/hr.h>
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
   
    vec featx, featy;
    test(x, new HR(100), featx);
    test(y, new HR(100), featy);
    
//     if (featx.size() != 1 || featy.size() != 1)
//         exit(1);

#ifdef PLOT
    Gnuplot* p1 = cli::plot_xy(t, x, "test");
    Gnuplot* p2 = cli::plot_x(sx, "abs(spectrum(test))");
    Gnuplot* p3 = cli::plot_xy(t, y, "silence");
    Gnuplot* p4 = cli::plot_x(sy, "abs(spectrum(silence))");
    cli::pressKey();
#endif

}
