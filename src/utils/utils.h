/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_UTILS_H
#define SVM_UTILS_H

#include <itpp/itbase.h>
using namespace itpp;

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

};

#endif
