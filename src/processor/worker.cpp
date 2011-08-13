/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "worker.h"

#define RLOG_COMPONENT "worker"
#include <rlog/rlog.h>

Worker::Worker(Feature* f) {
    extractor = f;
    rDebug("initialized worker for feature %s", extractor->getName().c_str());
}

Worker::~Worker() {
    rDebug("destroyed worker for feature %s", extractor->getName().c_str());
}

Type Worker::getFeatureType() const {
    return extractor->getType();
}

void Worker::start(const itpp::vec& data, itpp::vec& features) {
    thread = boost::thread(&Worker::extract, this, data, features);
}

void Worker::join() {
    thread.join();
}

void Worker::extract(const itpp::vec& data, itpp::vec& features) {
    extractor->extract(data, features);
}
    