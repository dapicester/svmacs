/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_UTILS_H
#define SVM_UTILS_H

#include "gnuplot_i.hpp"

#include <itpp/itbase.h>
using itpp::vec;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace utils {

/** Return a mirrored copy of the input vector. */
vec flipud(const vec& input) {
    const int len = input.length(); 
    vec output(len);
    for (int i=0, j=len-1; i<len; i++, j--) {
        output(i) = input(j);
    }
    
    return output;
}

}

namespace cli {

void pressKey () {
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();

    return;
}

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

};

#endif
