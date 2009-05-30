/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_UTILS_H
#define SVM_UTILS_H



#include <itpp/itbase.h>
using itpp::vec;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

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

};

#endif
