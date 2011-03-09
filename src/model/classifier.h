/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <model/event.h>

#include <itpp/itbase.h>

namespace model {

/** 
 * Interface to be implemented. 
 */
class Classifier {
public:
    static const char* EventDescription[4]; // TODO: eliminare

    /**
     * Process the audio features for detection 
     * and classification of events. 
     */
    virtual EventType classify(itpp::vec& features) const = 0;
};

}
#endif
