/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef WORKER_H
#define	WORKER_H

#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include "features/feature.h"

/**
 * @brief Worker thread for feature extraction.
 */
class Worker : public boost::noncopyable {
public:
    Worker(Feature* f);
    ~Worker();
    
    Type getFeatureType() const;
    
    /// Start the thread for feature extraction.
    void start(const itpp::vec& data, itpp::vec& features);
    /// Wait for thread termination.
    void join();

protected:
    /// Thread working method
    void extract(const itpp::vec& data, itpp::vec& features);
    
private:
    Feature* extractor;
    
    boost::thread thread;
};

#endif	/* WORKER_H */

