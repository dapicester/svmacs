/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef ENGINE_H
#define	ENGINE_H

class JackClient;
class Processor;
class Classifier;

#include "model/event.h"
#include "exceptions/exceptions.h"

#include <itpp/base/vec.h>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>

/**
 * This class contains the application business logic,
 * i.e. reading audio input data from the Jack client,
 * computing features and and using them classification.
 */ 
class Engine : boost::noncopyable {
public:
    /**
     * Constructor.
     * @param length 
     *          frame length (seconds)
     * @param overlap
     *          frames overlapping ratio (defaults to 0)
     */
    Engine(float length, float overlap = 0.0) 
            throw (JackException, BadModel);
    ~Engine();
    
    /**
     * Start processing.
     */
    void start();
    
    /**
     * Stop processing.
     */
    void stop();
    
    /**
     * Signal raised on event detection.
     */
    boost::signals2::signal<void (Event)> eventDetected;
    
private:
    /// The Jack audio client.
    JackClient* client;
    
    /// The audio frame processor.
    Processor* processor;

    /// The classifier.
    Classifier* classifier;
    
    mutable EventType previousEvent;

public:
    /// slot for input processing
    void processFrame(const itpp::vec& frame) const;
};

#endif	/* ENGINE_H */
