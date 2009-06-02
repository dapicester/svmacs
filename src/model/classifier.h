/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <itpp/base/vec.h>
using itpp::vec;

namespace model {

/// Type of detected event
enum EventType {
    NONE, GUNSHOT, SCREAM, GLASS
};

/** Interface to be implemented. */
class Classifier {

public:

/** Process the audio features for detection and classification of events. */
virtual EventType classify(vec& features) const = 0;

};

}

#endif
