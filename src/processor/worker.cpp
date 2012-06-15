/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "worker.h"

#define RLOG_COMPONENT "worker"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

Worker::Worker(Feature* f) {
    extractor = f;
    name = extractor->getName().c_str();
    rDebug("initialized worker for feature %s", name);
}

Worker::~Worker() {
    thread.join(); // ensure that processing is finished
    delete extractor;
    rDebug("destroyed worker for feature %s", name);
}

Type Worker::getFeatureType() const {
    return extractor->getType();
}

void Worker::start(const itpp::vec& data, itpp::vec* features) {
    thread = boost::thread(&Feature::extract, extractor, data, features);
    //thread.join(); // calling this it's like having no threads (serial execution)
}

void Worker::join() {
    thread.join();
}
 
NS_SVMACS_END
