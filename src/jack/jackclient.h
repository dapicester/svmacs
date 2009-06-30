/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include "../features/processor.h"
#include "../model/classifier.h"
using model::EventType;

#include "ringbufferread.h"
#include <jackaudioio.hpp>

#include <itpp/itsignal.h>
using namespace itpp; //TODO rimuovere using

#include <QObject>

namespace jack {

class JackClient : public QObject, public JackCpp::AudioIO {

    Q_OBJECT

    /// Maximum number of input ports
    static const uint MAX_IN = 1;
    /// Maximum number of output ports
    static const uint MAX_OUT = 1;
    
    /// Frame length in samples
    uint N;
    /// Frame overlap in samples
    uint R; 

    /// Input buffer
    RingBufferRead input;
    /// Current frame
    double* frame;
    
    /// Audio frame processor
    features::Processor processor;
    
    /// Audio classifier
    model::Classifier* classifier;
    
     /// Constructor
    JackClient(float length, float overlap);
     /// Copy-constructor
    JackClient(JackClient&);
    
    /// Initializations
    void init();
    
public:
    /** Get the Jack client instance
     * \param length frame length in seconds (defaults to 1 second)
     * \param overlap percentage of frame overlap (defaults to 0)
     */
    static JackClient* getInstance(float length = 1.0, float overlap = 0.0);

    /// Destructor
    ~JackClient();
    
    /// Numberof input ports (mono input)
    static const uint NUM_INPUT = 1;
    /// Number of output ports (monitor output) 
    static const uint NUM_OUTPUT = 1;
    
    /** Audio callback. All audio processing goes in this function. */
    int audioCallback(jack_nframes_t nframes, 
                      audioBufVector inBufs,
                      audioBufVector outBufs);
    
signals:
    void eventDetected(EventType type);

private:    
    /// Process samples from the input buffer
    void processFrame();
    
};

}

#endif // JACKCLIENT_H
