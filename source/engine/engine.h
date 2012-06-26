/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef ENGINE_H
#define	ENGINE_H

#include "config.h"
#include "model/event.h"
#include "exceptions/exceptions.h"

#include <itpp/base/vec.h>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>

NS_SVMACS_BEGIN

class JackClient;
class Processor;
class Classifier;

/**
 * This class contains the application business logic,
 * i.e. reading audio input data from the Jack client,
 * computing features and and using them classification.
 */ 
class Engine : private boost::noncopyable {
public:
    /**
     * Constructor.
     * @param length 
     *          frame length (seconds)
     * @param overlap
     *          frames overlapping ratio (percentage)
     * @param dmodel
     *          path to the detection model file
     * @param cmodel
     *          path to the classification model file
     */
    Engine(float length, float overlap, const std::string& dmodel,
            const std::string& cmodel) throw (JackException, BadModel);

    /// Destructor.
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
    
private: // TODO: boost::scoped_ptr
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

NS_SVMACS_END

#endif	/* ENGINE_H */
