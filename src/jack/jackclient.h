/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include "../features/processor.h"

#include "ringbufferread.h"
#include <jackaudioio.hpp>

namespace jack {

class JackClient : public JackCpp::AudioIO {

    static const uint MAX_IN = 1;
    static const uint MAX_OUT = 1;
    
    /// Frame overlap in samples
    uint R; 
    /// Frame length in samples
    uint N;
    /// Input buffer
    RingBufferRead input;
    /// Current frame
    //RingBufferRead buffer; 
    double* frame;
    
    /// Audio frame processor
    features::Processor processor;
    
     /// Constructor
    JackClient(float overlap);
     /// Copy-constructor
    JackClient(JackClient&);
    
    /// Initializations
    void init();
    
public:
    /** Get the Jack client instance */
    static JackClient* getInstance(float overlap = 0.0);

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
                                                           
private:
    /** Read one audio frame */
    void getAudioFrame();
};

}

#endif // JACKCLIENT_H
