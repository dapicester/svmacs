/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "model/event.h"

#include <itpp/base/vec.h>

/** 
 * Interface to be implemented. 
 */
class Classifier {
public:
    /**
     * Process the audio features for detection 
     * and classification of events. 
     */
    virtual EventType classify(itpp::vec& features) const = 0;
};

#endif
