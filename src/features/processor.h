/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "feature.h"

namespace features {

class Processor {
    int sampleRate;

    static const int fsize = 2;
    /** Features extractors */
    Feature* features[fsize];
    
public:
    Processor(int sr);
    ~Processor();

    /** Process an audio frame and returns its features */
    float* process(const float frame[]);
};

}

#endif
