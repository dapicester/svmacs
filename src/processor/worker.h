/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef WORKER_H
#define	WORKER_H

#include "config.h"
#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include "features/feature.h"

// FIXME: remove this class!!

NS_SVMACS_BEGIN

/**
 * @brief Worker thread for feature extraction.
 */
class Worker : public boost::noncopyable {
public:
    Worker(Feature* f);
    ~Worker();
    
    Type getFeatureType() const;
    
    /// Start the thread for feature extraction.
    void start(const itpp::vec& data, itpp::vec* features);
    
    /// Wait for thread termination.
    void join();

private:
    Feature* extractor;
    const char* name;
    
    boost::thread thread;
};

NS_SVMACS_END

#endif	/* WORKER_H */
