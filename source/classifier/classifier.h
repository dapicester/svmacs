/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "config.h"
#include "model/event.h"

#include <boost/noncopyable.hpp>
#include <itpp/base/vec.h>

NS_SVMACS_BEGIN

/**
 * Interface to be implemented.
 */
class Classifier : private boost::noncopyable {
public:

    virtual ~Classifier() {}

    /**
     * Process the audio features for detection
     * and classification of events.
     */
    virtual EventType classify(itpp::vec& features) const = 0;
};

NS_SVMACS_END

#endif
