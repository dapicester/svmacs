/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef PLOT_H
#define PLOT_H

#include "gnuplot_i.hpp"

#include <string>
using std::string;

Gnuplot* plot_x(const vec& x, const string& title = "") {
    Gnuplot* p = new Gnuplot("test");
    p->set_grid();
    p->set_style("lines");
    p->plot_x(x, title);
    p->showonscreen();
    return p;
}

Gnuplot* plot_xy(const vec& x, const vec& y, const string& title = "") {
    Gnuplot* p = new Gnuplot("test");
    p->set_grid();
    p->set_style("lines");
    p->plot_xy(x, y, title);
    p->showonscreen();
    return p;
}

#endif
